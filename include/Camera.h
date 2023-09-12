#pragma once
#include "../include/glm/glm.hpp"
#include "../include/ColorRGB.h"
#include <fstream>
#include <vector>
#include <string>

class Camera {
public:
	Camera(int w, int h);

	int GetWidth(); // Get the width of the camera
	int GetHeight(); // Get the height of the camera
	glm::vec4 GetLocation(int x, int y); // Get the location of the camera
	glm::vec4 SetLocation(int x, int y, int z); // Set the location of the camera
	void saveImage(std::string filename, int width, int height, const std::vector<std::vector<ColorRGB>>& pixels); // Saves the generated image to a file (PPM-format)

	std::vector<std::vector<ColorRGB>> pixels;

private:
	int width;
	int height;
	glm::vec4 Location;
};
