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

void Camera::castRays(const std::vector<Polygon*>& polygons, std::vector<Sphere*> spheres, const std::vector<Light*>& lights) {

	float progress = 0.0f;
	int depth = 5;

	// Loopar igenom alla pixlar
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {

			Ray ray(location, calculateRayDirectionFromCamera(i, j));

			// Kollar intersections som sker i scenen  
			handleIntersection(polygons, spheres, lights, ray, i, j, depth);

			// Visar progress under rendrering
			progressBar(progress / (height * width));
			progress += 1.0f;
		}
	}
}


void Camera::handleIntersection(const std::vector<Polygon*>& polygons, std::vector<Sphere*> spheres, const std::vector<Light*>& lights, const Ray& ray, int i, int j, int depth) {
	const float EPSILON = 1e-4f;

	IntersectionResult result = findClosestIntersection(polygons, spheres, ray);

	float t = result.t;
	int index = result.index;
	IntersectionType type = result.type;

	// Exit if the maximum recursion depth is reached
	if (depth <= 0) {
		return;
	}

	if (t > EPSILON && t < FLT_MAX) {
		glm::vec3 intersectionPoint = ray.at(t);
		glm::vec3 intersectionPointNormal;

		if (type == POLYGON) {
			intersectionPointNormal = polygons[index]->getNormal();
		}
		else if (type == SPHERE) {
			intersectionPointNormal = spheres[index]->getNormal(intersectionPoint);
		}

		if (type == POLYGON && polygons[index]->getMaterial().type == REFLECTIVE ||
			type == SPHERE && spheres[index]->getMaterial().type == REFLECTIVE) {
			handleReflection(polygons, spheres, lights, ray, intersectionPoint, intersectionPointNormal, i, j, depth);
		}
		else {
			handleDiffuse(polygons, spheres, lights, intersectionPoint, intersectionPointNormal, type, index, i, j);
		}
	}
}

void Camera::handleReflection(const std::vector<Polygon*>& polygons, std::vector<Sphere*> spheres, const std::vector<Light*>& lights, const Ray& ray, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, int i, int j, int depth) {
	glm::vec3 reflectionDirection = glm::reflect(ray.getDirection(), intersectionPointNormal);
	Ray reflectedRay(intersectionPoint, reflectionDirection);

	// Recursively trace the reflected ray with reduced depth
	handleIntersection(polygons, spheres, lights, reflectedRay, i, j, depth - 1);
}

void Camera::handleDiffuse(const std::vector<Polygon*>& polygons, std::vector<Sphere*> spheres, const std::vector<Light*>& lights, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, IntersectionType type, int index, int i, int j) {
	ColorRGB color;

	if (type == POLYGON) {
		color = polygons[index]->getMaterial().diffuseData.color;
	}
	else if (type == SPHERE) {
		color = spheres[index]->getMaterial().diffuseData.color;
	}

	float irradiance = 0.0f;

	for (Light* light : lights) {
		irradiance += light->calculateLight(polygons, spheres, intersectionPoint, intersectionPointNormal);
	}

	// Set the color of the pixel
	pixels[j][i] = color * irradiance;
}


glm::vec3 Camera::calculateRayDirectionFromCamera(int i, int j) {
	// Beräknar u och v (positionen i world coordinates)
	// u och v är mellan -1 och 1
	float u = 1.0f - (2.0f * i) / width;
	float v = 1.0f - (2.0f * j) / height;

	// Returnerar en normaliserad vektor fr�n kamerans position till u och v
	return glm::normalize(glm::vec3(0.0f, u, v) - location);
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

IntersectionResult findClosestIntersection(const std::vector<Polygon*>& polygons, std::vector<Sphere*> spheres, const Ray& ray) {
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