#pragma once
#include "../include/glm/glm.hpp"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"
#include <fstream>
#include <vector>
#include <string>

class Camera {
public:
	Camera(int w, int h);

	int getWidth(); // Get the width of the camera
	int getHeight(); // Get the height of the camera
	glm::vec3 getLocation(); // Get the location of the camera
	void saveImage(std::string filename, int width, int height, const std::vector<std::vector<ColorRGB>>& pixels); // Save the image to a file (PPM-format)
	void traceRays(std::vector<std::vector<ColorRGB>>& pixels, const std::vector<Polygon*>& objects); // Trace the rays from the camera to the objects
	glm::vec3 calculateRayDirection(int i, int j);
	std::vector<std::vector<ColorRGB>> pixels;

private:
	int width;
	int height;
	glm::vec3 location{ -1.0f, 0.0f, 0.0f };
};
