#pragma once
#include "../include/glm/glm.hpp"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"
#include "../include/Light.h"
#include <fstream>
#include <vector>
#include <string>

class Camera {
public:
	Camera(int w, int h);

	int getWidth(); 
	int getHeight(); 
	glm::vec3 getLocation(); 
	void saveImage(std::string filename); 
	void traceRays(const std::vector<Polygon*>& objects, const std::vector<Light*>& lights);
	glm::vec3 calculateRayDirection(int i, int j);
	std::vector<std::vector<ColorRGB>> pixels;

private:
	int width;
	int height;
	glm::vec3 location{ -1.0f, 0.0f, 0.0f };
	glm::vec3 intersectionPoint{ 0.0f, 0.0f, 0.0f };
};
