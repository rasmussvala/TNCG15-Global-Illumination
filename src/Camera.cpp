#pragma once

#include "../include/Camera.h"
#include "../include/Light.h"
#include "../include/Cube.h"
#include "../include/Sphere.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

Camera::Camera(int w, int h) : width(w), height(h) {
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
	const int depth = 5;

	// Loopar igenom alla pixlar
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {

			Ray ray(location, rayDirectionFromCamera(i, j));

			// Kollar intersections som sker i scenen  
			ColorRGB colorOfPixel = { 0.0, 0.0, 0.0 };
			castRay(ray, depth, colorOfPixel);
			pixels[j][i] = colorOfPixel;

			// Visar progress under rendrering
			progressBar(progress / (height * width));
			progress += 1.0f;
		}
	}
}


void Camera::castRay(const Ray& ray, int depth, ColorRGB& color) {
	
	// Exit if the maximum recursion depth is reached
	if (depth <= 0) {
		return;
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
			handleReflection(ray, intersectionPoint, intersectionPointNormal, depth, color);
		}
		else if (type == POLYGON && materialType == DIFFUSE ||
			type == SPHERE && materialType == DIFFUSE) {
			handleDiffuse(intersectionPoint, intersectionPointNormal, type, index, depth, color);
		}
		else {
			// TRANSPARENT
			// handleTransparent(/* add stuff */);
		}
	}
}

void Camera::handleTransparent(const Ray& ray, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, const Material& transparentMaterial, int depth) {
	glm::vec3 reflectionDirection = glm::reflect(ray.getDirection(), intersectionPointNormal);
	reflectionDirection = glm::normalize(reflectionDirection);
	Ray reflectedRay(intersectionPoint, reflectionDirection);

	// Calculate the refraction direction using Snell's law
	float eta = transparentMaterial.transparentData.refractiveIndex;

	glm::vec3 refractionDirection = glm::refract(ray.getDirection(), intersectionPointNormal, eta);
	refractionDirection = glm::normalize(refractionDirection);
	Ray refractedRay(intersectionPoint, refractionDirection);

	
	// Implement Fresnel equations to determine reflectance and transmittance
	// float reflectance = calculateReflectance(ray.getDirection(), intersectionPointNormal, eta);

	//	// Trace both reflected and refracted rays recursively
	//	ColorRGB reflectedColor = traceRay(reflectedRay, depth - 1);
	//	ColorRGB refractedColor = traceRay(refractedRay, depth - 1);

	//	// Combine the reflected and refracted colors based on Fresnel reflectance
	//	ColorRGB finalColor = reflectance * reflectedColor + (1.0 - reflectance) * refractedColor;
	//}
	//else {
	//	// Total internal reflection, only handle reflection
	//	ColorRGB finalColor = traceRay(reflectedRay, depth - 1);

	//// Apply the finalColor to the pixel.
}

void Camera::handleReflection(const Ray& ray, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, int depth, ColorRGB& color) {
	glm::vec3 reflectionDirection = glm::reflect(ray.getDirection(), intersectionPointNormal);
	Ray reflectedRay(intersectionPoint, reflectionDirection);

	// Recursively trace the reflected ray with reduced depth
	castRay(reflectedRay, depth - 1, color);
}

void Camera::handleDiffuse(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, IntersectionType type, int index, int depth, ColorRGB& color) {
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

	// Set the color of the pixel
	color += colorOfObject * irradiance;

	// ska skicka ut N antal nya rays från sig själv
	const int N = 5;

	for (int i = 0; i < N; ++i) {
		Ray randomRay(intersectionPoint, randomRayDirection(intersectionPoint, intersectionPointNormal));
		castRay(randomRay, depth - 1, color);
	}
}


glm::vec3 Camera::rayDirectionFromCamera(int i, int j) {
	// Beräknar u och v (positionen i world coordinates)
	// u och v är mellan -1 och 1
	float u = 1.0f - (2.0f * i) / width;
	float v = 1.0f - (2.0f * j) / height;

	// Returnerar en normaliserad vektor fr�n kamerans position till u och v
	return glm::normalize(glm::vec3(0.0f, u, v) - location);
}

glm::vec3 Camera::randomRayDirection(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal) {

	const float TWO_PI = 6.28318530718f;
	const float PI = 3.14159265359f;

	// Generate random spherical coordinates
	float inclination = (static_cast<float>(rand()) / RAND_MAX) * TWO_PI;
	float azimuth = (static_cast<float>(rand()) / RAND_MAX) * PI;

	// Convert spherical coordinates to Cartesian coordinates in the local hemisphere
	glm::vec3 localDirection = HemisphericalToLocalCartesian(azimuth, inclination);

	// Convert the local direction to the world coordinate system
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

inline glm::vec3 Camera::HemisphericalToLocalCartesian(double phi, double omega) {
	float sinOmega = sin(omega);
	return glm::vec3(
		sinOmega * cos(phi),
		sinOmega * sin(phi),
		cos(omega)
	);
}

// WIP
inline glm::vec3 Camera::LocalCartesianToWorldCartesian(const glm::vec3& localDirection, const glm::vec3& normal) {
	float x0 = localDirection.x;
	float y0 = localDirection.y;
	float z0 = localDirection.z;

	glm::vec3 c = normal;
	glm::vec3 a = glm::normalize(-localDirection + glm::dot(normal, localDirection) * normal);
	glm::vec3 b = glm::cross(c, a);

	glm::vec3 worldDirection(
		x0 * a.x + y0 * b.x + z0 * c.x,
		x0 * a.y + y0 * b.y + z0 * c.y,
		x0 * a.z + y0 * b.z + z0 * c.z
	);

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