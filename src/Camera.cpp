#include "../include/Camera.h"
#include "../include/Light.h"
#include "../include/Cube.h"
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

int Camera::getWidth() {
	return width;
}

int Camera::getHeight() {
	return height;
}

glm::vec3 Camera::getLocation() {
	return glm::vec3();
}

//void Camera::saveImage(std::string filename) {
//	std::ofstream ppmFile(filename); // �ppnar/skapar filen
//
//	ppmFile << "P3\n" << width << ' ' << height << "\n255\n";
//
//	for (int j = 0; j < height; ++j) {
//		for (int i = 0; i < width; ++i) {
//
//			auto r = pixels[j][i].r;
//			auto g = pixels[j][i].g;
//			auto b = pixels[j][i].b;
//
//			// Convert from floats [0,1] to ints [0,255]
//			int ir = static_cast<int>(255.999 * r);
//			int ig = static_cast<int>(255.999 * g);
//			int ib = static_cast<int>(255.999 * b);
//
//			ppmFile << ir << ' ' << ig << ' ' << ib << '\n';
//		}
//	}
//	ppmFile.close();
//}

// CONTRAST STRETCHING
void Camera::saveImage(std::string filename) {

	std::ofstream ppmFile(filename); // Opens/creates the file

	ppmFile << "P3\n" << width << ' ' << height << "\n255\n";

	// Find the maximum pixel value among all channels
	float maxRGB = -FLT_MAX;

	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {
			auto r = pixels[j][i].r;
			auto g = pixels[j][i].g;
			auto b = pixels[j][i].b;

			float maxChannel = std::max({ r, g, b });
			maxRGB = std::max(maxRGB, maxChannel);
		}
	}

	// Calculate the stretching factor
	float stretchFactor = 255.0 / maxRGB;

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

void Camera::traceRays(const std::vector<Polygon*>& polygons, const std::vector<Light*>& lights) {

	float progress = 0.0f;

	// Loopar igenom alla pixlar
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {

			Ray ray(location, calculateRayDirection(i, j));

			// Rendrerar alla polygoner (rum + kub) 
			renderPolygons(polygons, lights, ray, i, j);

			// Rendrerar ljuskällorna i rummet
			renderLights(lights, ray, j, i);

			// Visar progress under rendrering
			progressBar(progress / (height * width));
			progress += 1.0f;
		}
	}
}

void Camera::renderLights(const std::vector<Light*>& lights, Ray& ray, int j, int i)
{
	// Rendrerar objektet i scenen
	const float EPSILON = 1e-4;

	// Rendrera ljus 
	for (const auto& light : lights) {
		float t = light->getGeometry().intersect(ray);

		if (t > EPSILON) {
			pixels[j][i] = { 1.0f, 1.0f, 1.0f };
		}
	}
}

void Camera::renderPolygons(const std::vector<Polygon*>& polygons, const std::vector<Light*>& lights, const Ray& ray, int i, int j) {
	const float EPSILON = 1e-4;

	IntersectionResult result = findSmallestTAndIndex(polygons, ray);

	float smallestT = result.smallestT;
	int smallestIndex = result.smallestIndex;

	// Går in här om vi har hittat kortaste snittet
	if (smallestT > EPSILON && smallestT < FLT_MAX) {

		glm::vec3 intersectionPoint = ray.at(smallestT);
		glm::vec3 intersectionPointNormal = polygons[smallestIndex]->getNormal();

		// Spegel
		if(polygons[smallestIndex]->getMaterial().type == Reflective) {
			glm::vec3 reflectionDirection = glm::reflect(ray.getDirection(), intersectionPointNormal);
			Ray reflectedRay(intersectionPoint, reflectionDirection);

			// Trace the reflected ray with increased depth
			renderPolygons(polygons, lights, reflectedRay, i, j);
		}
		else {
			ColorRGB color = polygons[smallestIndex]->getMaterial().diffuseData.color;

			float irradiance = 0.0f;

			for (Light* light : lights) {
				irradiance = light->calculateLight(intersectionPoint, intersectionPointNormal, polygons);
			}

			// Ansätter färgen på pixeln 
			pixels[j][i] = color * irradiance;
		}
	}
}

glm::vec3 Camera::calculateRayDirection(int i, int j) {
	// Beräknar u och v (positionen i world coordinates)
	// u och v är mellan -1 och 1
	float u = (2.0f * i) / width - 1.0f; // går från -1 -> 1
	float v = 1.0f - (2.0f * j) / height; // går från 1 -> -1

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

IntersectionResult findSmallestTAndIndex(const std::vector<Polygon*>& polygons, const Ray& ray) {
	const float EPSILON = 1e-4;
	float smallestT = FLT_MAX;
	std::vector<float> t_values;

	// Kollar igenom alla polygons, och hittar alla snitt
	for (const auto& poly : polygons) {
		t_values.push_back(poly->intersect(ray));
	}

	int smallestIndex = -1; // Initialize to an invalid index

	// Ansätter det närmaste snittet
	for (int i = 0; i < t_values.size(); i++) {
		if (t_values[i] > EPSILON && t_values[i] < smallestT) {
			smallestT = t_values[i];
			smallestIndex = i;
		}
	}

	return { smallestT, smallestIndex };
}