#include "../include/Camera.h"
#include <fstream>
#include <iostream>

Camera::Camera(int w, int h) : width(w), height(h), location(-1, 0, 0, 1) {
}

int Camera::getWidth() {
	return width;
}

int Camera::getHeight() {
	return height;
}

glm::vec4 Camera::getLocation() {
	return glm::vec4();
}

void Camera::saveImage(std::string filename, int width, int height, const std::vector<std::vector<ColorRGB>>& pixels) {

	std::ofstream ppmFile(filename); // Open a file for writing

	ppmFile << "P3\n" << width << ' ' << height << "\n255\n";

	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {

			auto r = double(i) / (width - 1);
			auto g = double(j) / (height - 1);
			auto b = 0;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			ppmFile << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}

	ppmFile.close(); // Close the file
}


