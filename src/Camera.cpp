#include "../include/Camera.h"
#include "../include/Light.h"
#include "../include/Object.h"
#include <fstream>
#include <iostream>

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

#include <vector>
#include <algorithm>

void Camera::saveImage(std::string filename) {

	// NO CONTRAST STRETCHING

	std::ofstream ppmFile(filename); // �ppnar/skapar filen

	ppmFile << "P3\n" << width << ' ' << height << "\n255\n";

	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {

			auto r = pixels[j][i].r;
			auto g = pixels[j][i].g;
			auto b = pixels[j][i].b;

			// Convert from floats [0,1] to ints [0,255]
			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			ppmFile << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}

	ppmFile.close();
}


void Camera::traceRays(const std::vector<Polygon*>& polygons, const std::vector<Light*>& lights, const std::vector<Object*>& objects) {

	float progress = 0.0f;

	// Loopar igenom alla pixlar
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {

			Ray ray(location, calculateRayDirection(i, j));

			// Rendrerar rummet
			renderRoom(polygons, lights, objects, ray, i, j);

			// Rendrerar alla objekt i rummet 
			renderObjects(objects, lights, ray, i, j);

			// Rendrerar objektet i scenen
			const float EPSILON = 1e-6;

			// Rendrera obj 
			for (const auto& light : lights) {
				float t = light->getGeometry().intersect(ray);

				if (t > EPSILON) {
					pixels[j][i] = { 1.0f, 1.0f, 1.0f };
				}
			}

			// Visar progress under rendrering
			progressBar(progress / (height * width));
			progress += 1.0f;
		}
	}
}

void Camera::renderObjects(const std::vector<Object*>& objects, const std::vector<Light*>& ligths, const Ray& ray, int i, int j)
{
	// Rendrerar objektet i scenen
	const float EPSILON = 1e-6;

	// Rendrera obj 
	for (const auto& obj : objects) {
		float t = obj->intersect(ray);

		if (t > EPSILON) {
			glm::vec3 intersectionPoint = ray.at(t);
			glm::vec3 intersectionPointNormal = obj->getNormal(intersectionPoint);
			float irradiance = 0.0f;

			for (Light* light : ligths) {
				irradiance = light->calculateLight(intersectionPoint, intersectionPointNormal, objects);
			}

			// Ansätter färgen på pixeln 
			pixels[j][i] = { obj->getColor().r * irradiance,
				obj->getColor().g * irradiance,
				obj->getColor().b * irradiance
			};
		}
	}
}

void Camera::renderRoom(const std::vector<Polygon*>& polygons, const std::vector<Light*>& lights, const std::vector<Object*>& objects, const Ray& ray, int i, int j) {

	const float EPSILON = 1e-6;

	// Kollar om ray intersectar något objekt
	for (const Polygon* obj : polygons) {

		float t = obj->intersect(ray);

		if (t > EPSILON) {

			glm::vec3 intersectionPoint = ray.at(t);
			glm::vec3 intersectionPointNormal = obj->getNormal();
			float irradiance = 0.0f;

			for (Light* light : lights) {
				irradiance = light->calculateLight(intersectionPoint, intersectionPointNormal, objects);
			}

			// Ansätter färgen på pixeln 
			pixels[j][i] = { obj->getColor().r * irradiance,
				obj->getColor().g * irradiance,
				obj->getColor().b * irradiance };
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