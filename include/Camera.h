#pragma once
#include "../include/glm/glm.hpp"
#include "../include/ColorRGB.h"
#include <fstream>
#include <vector>
#include <string>

class Camera {
public:
	Camera(int w, int h);

	int getWidth(); // Get the width of the camera
	int getHeight(); // Get the height of the camera
	glm::vec4 getLocation(); // Get the location of the camera
	void saveImage(std::string filename, int width, int height, const std::vector<std::vector<ColorRGB>>& pixels); // Save the image to a file (PPM-format)
	std::vector<std::vector<ColorRGB>> pixels;

private:
	int width;
	int height;
	glm::vec4 location;
};
