#pragma once

#include "../include/Camera.h"
#include "../include/Light.h"
#include "../include/Cube.h"
#include "../include/Sphere.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

Camera::Camera(int w, int h) : width(w), height(h) {
	MAX_DEPTH = 0;

	// Allokera minne för pixels
	pixels.resize(height);
	for (int i = 0; i < height; ++i) {
		pixels[i].resize(width);
	}
}

void Camera::saveImage(std::string filename) {
	// CONTRAST STRETCHING
	std::ofstream ppmFile(filename); // Opens/creates the file

	ppmFile << "P3\n" << width << ' ' << height << "\n255\n";

	// Find the maximum pixel value among all channels
	float maxRGB = -FLT_MAX;

	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {
			auto r = pixels[j][i].r;
			auto g = pixels[j][i].g;
			auto b = pixels[j][i].b;

			float maxChannel = (float)std::max({ r, g, b });
			maxRGB = (float)std::max(maxRGB, maxChannel);
		}
	}

	// Calculate the stretching factor
	float stretchFactor = 255.0f / maxRGB;

	// Write the stretched pixel values to the output file
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {
			auto r = pixels[j][i].r;
			auto g = pixels[j][i].g;
			auto b = pixels[j][i].b;

			// Convert to 0-255
			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);
			// Apply contrast stretching using the brightest channel
			ir = static_cast<int>(stretchFactor * r);
			ig = static_cast<int>(stretchFactor * g);
			ib = static_cast<int>(stretchFactor * b);

			ppmFile << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
	ppmFile.close();
}

void Camera::castRays() {

	float progress = 0.0f;

	// Loopar igenom alla pixlar
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {

			Ray ray(location, rayDirectionFromCamera(i, j));

			// Kollar intersections som sker i scenen  
			pixels[j][i] = castRay(ray, MAX_DEPTH);

			// Visar progress under rendrering
			progressBar(progress / (height * width));
			progress += 1.0f;
		}
	}
}

ColorRGB Camera::castRay(const Ray& ray, int depth) {

	ColorRGB color;

	if (depth <= 0) {
		return color;
	}

	const float EPSILON = 1e-4f;

	IntersectionResult result = closestIntersection(ray, polygons, spheres);

	float t = result.t;
	int index = result.index;
	IntersectionType type = result.type;

	if (t > EPSILON && t < FLT_MAX) {
		glm::vec3 intersectionPoint = ray.at(t);
		glm::vec3 intersectionPointNormal;
		MaterialType materialType;

		if (type == POLYGON) {
			intersectionPointNormal = polygons[index]->getNormal();
			materialType = polygons[index]->getMaterial().type;
		}
		else if (type == SPHERE) {
			intersectionPointNormal = spheres[index]->getNormal(intersectionPoint);
			materialType = spheres[index]->getMaterial().type;
		}

		if (type == POLYGON && materialType == REFLECTIVE ||
			type == SPHERE && materialType == REFLECTIVE) {
			color = handleReflection(ray, intersectionPoint, intersectionPointNormal, depth);
		}
		else if (type == POLYGON && materialType == DIFFUSE ||
			type == SPHERE && materialType == DIFFUSE) {
			ColorRGB direct = directLight(intersectionPoint, intersectionPointNormal, type, index, depth);
			ColorRGB indirect = indirectLight(depth, intersectionPoint, intersectionPointNormal);
			
			color = direct + (indirect * 0.5f);
		}
	}

	return color;
}

//void Camera::handleTransparent(const Ray& ray, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, const Material& transparentMaterial, int depth) {
//	glm::vec3 reflectionDirection = glm::reflect(ray.getDirection(), intersectionPointNormal);
//	reflectionDirection = glm::normalize(reflectionDirection);
//	Ray reflectedRay(intersectionPoint, reflectionDirection);
//
//	// Calculate the refraction direction using Snell's law
//	float eta = transparentMaterial.transparentData.refractiveIndex;
//
//	glm::vec3 refractionDirection = glm::refract(ray.getDirection(), intersectionPointNormal, eta);
//	refractionDirection = glm::normalize(refractionDirection);
//	Ray refractedRay(intersectionPoint, refractionDirection);
//
//
//	// Implement Fresnel equations to determine reflectance and transmittance
//	// float reflectance = calculateReflectance(ray.getDirection(), intersectionPointNormal, eta);
//
//	//	// Trace both reflected and refracted rays recursively
//	//	ColorRGB reflectedColor = traceRay(reflectedRay, depth - 1);
//	//	ColorRGB refractedColor = traceRay(refractedRay, depth - 1);
//
//	//	// Combine the reflected and refracted colors based on Fresnel reflectance
//	//	ColorRGB finalColor = reflectance * reflectedColor + (1.0 - reflectance) * refractedColor;
//	//}
//	//else {
//	//	// Total internal reflection, only handle reflection
//	//	ColorRGB finalColor = traceRay(reflectedRay, depth - 1);
//
//	//// Apply the finalColor to the pixel.
//}

ColorRGB Camera::handleReflection(const Ray& ray, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, int depth) {
	glm::vec3 reflectionDirection = glm::reflect(ray.getDirection(), intersectionPointNormal);
	Ray reflectedRay(intersectionPoint, reflectionDirection);

	if (depth == MAX_DEPTH && MAX_DEPTH != 1) {
		return castRay(reflectedRay, depth);
	}
	else {
		return castRay(reflectedRay, depth - 1);
	}
}

ColorRGB Camera::directLight(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, IntersectionType type, int index, int depth) {
	ColorRGB colorOfObject;

	if (type == POLYGON) {
		colorOfObject = polygons[index]->getMaterial().diffuseData.color;
	}
	else if (type == SPHERE) {
		colorOfObject = spheres[index]->getMaterial().diffuseData.color;
	}

	float irradiance = 0.0f;

	for (Light* light : lights) {
		irradiance += light->calculateLight(polygons, spheres, intersectionPoint, intersectionPointNormal);
	}

	return colorOfObject * irradiance;
}

ColorRGB Camera::indirectLight(int depth, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal) {
	ColorRGB indirect;
	int n = 4;

	for (int i = 0; i < n; i++) {
		Ray randomRay(intersectionPoint, randomRayDirection(intersectionPointNormal));
		indirect += castRay(randomRay, depth - 1);
	}

	indirect = indirect / n;
	return indirect;
}

glm::vec3 Camera::rayDirectionFromCamera(int i, int j) {
	// Beräknar u och v (positionen i world coordinates)
	// u och v är mellan -1 och 1
	float u = 1.0f - (2.0f * i) / width;
	float v = 1.0f - (2.0f * j) / height;

	// Returnerar en normaliserad vektor fr�n kamerans position till u och v
	return glm::normalize(glm::vec3(0.0f, u, v) - location);
}

glm::vec3 Camera::randomRayDirection(const glm::vec3& intersectionPointNormal) {

	const float PI = 3.14159265359f;

	float yi = static_cast<float>(rand()) / RAND_MAX; // random value [0,1]
	float phi = 2.0f * PI * yi; // azimuth
	float omega = acos(sqrt(1.0f - yi)); // inclination

	glm::vec3 localDirection = HemisphericalToLocalCartesian(phi, omega);

	glm::vec3 worldDirection = LocalCartesianToWorldCartesian(localDirection, intersectionPointNormal);

	// Make sure the direction is not pointing back into the surface
	if (glm::dot(worldDirection, intersectionPointNormal) < 0.0f) {
		worldDirection = -worldDirection;
	}

	worldDirection = glm::normalize(worldDirection);
	return worldDirection;
}

void Camera::progressBar(float percent) {
	const int BAR_WIDTH = 20;

	std::cout << "[";
	int pos = (int)(BAR_WIDTH * percent);
	for (int i = 0; i < BAR_WIDTH; ++i) {
		if (i <= pos)
			std::cout << "=";
		else
			std::cout << " ";
	}
	std::cout << "] " << int(percent * 100.0f + 0.5f)
		<< " %\r"; // +0.5 for round-off error
	std::cout.flush();
}

glm::vec3 Camera::HemisphericalToLocalCartesian(float phi, float omega) {
	float sinOmega = sin(omega);
	return glm::vec3(
		cos(phi) * sinOmega,
		sin(phi) * sinOmega,
		cos(omega)
	);
}

glm::vec3 Camera::LocalCartesianToWorldCartesian(const glm::vec3& localDirection, const glm::vec3& normal) {
	glm::vec3 c = normal;
	glm::vec3 a = glm::normalize(-localDirection + glm::dot(normal, localDirection) * normal);
	glm::vec3 b = glm::cross(c, a);

	glm::mat3 transformationMatrix(a, b, c);
	glm::vec3 worldDirection = transformationMatrix * localDirection;

	return worldDirection;
}

IntersectionResult closestIntersection(const Ray& ray, const std::vector<Polygon*>& polygons, const std::vector<Sphere*> spheres) {
	const float EPSILON = 1e-4f;
	float closestT = FLT_MAX;
	std::vector<float> t_values;
	IntersectionType closestType = NONE;
	int closestIndex = -1; // Initialize to an invalid index

	// Check intersections with polygons
	for (int i = 0; i < polygons.size(); i++) {
		float t = polygons[i]->intersect(ray);
		if (t > EPSILON && t < closestT) {
			closestT = t;
			closestType = POLYGON;
			closestIndex = i;
		}
	}

	// Check intersections with spheres
	for (int i = 0; i < spheres.size(); i++) {
		float t = spheres[i]->intersect(ray);
		if (t > EPSILON && t < closestT) {
			closestT = t;
			closestType = SPHERE;
			closestIndex = i;
		}
	}

	return { closestT, closestIndex, closestType };
}