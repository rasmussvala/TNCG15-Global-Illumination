#include "../include/Camera.h"
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

void Camera::saveImage(std::string filename) {

	std::ofstream ppmFile(filename); // Öppnar/skapar filen

	ppmFile << "P3\n" << width << ' ' << height << "\n255\n";

	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {

			auto r = pixels[j][i].r;
			auto g = pixels[j][i].g;
			auto b = pixels[j][i].b;

			// Convert to 0-255
			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			ppmFile << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}

	ppmFile.close();
}

void Camera::traceRays(const std::vector<Polygon*>& objects) {
	// Loopar igenom alla pixlar
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {

			// Skapar en ray för varje pixel
			Ray ray(location, calculateRayDirection(i, j));
			glm::vec3 intersectionPoint;

			// Kollar om ray intersectar något objekt
			for (const auto& obj : objects) {
				if (obj->intersect(ray, intersectionPoint)) {

					// Ansätter färgen på pixeln 
					pixels[j][i] = obj->getColor();

					break;
				}
			}
		}
	}
}

glm::vec3 Camera::calculateRayDirection(int i, int j) {
	// Beräknar u och v (positionen i world coordinates)
	// u och v är mellan -1 och 1
	float u = (2.0f * i) / width - 1.0f; // går från -1 -> 1
	float v = 1.0f - (2.0f * j) / height; // går från 1 -> -1

	// Returnerar en normaliserad vektor från kamerans position till u och v
	return glm::normalize(glm::vec3(0.0f, u, v) - location);
}