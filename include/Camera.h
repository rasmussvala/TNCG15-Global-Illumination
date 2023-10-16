#pragma once
#include "../include/glm/glm.hpp"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"
#include "../include/Light.h"
#include "../include/Cube.h"
#include <fstream>
#include <vector>
#include <string>

struct IntersectionResult {
	float smallestT;
	int smallestIndex;
};

IntersectionResult findSmallestTAndIndex(const std::vector<Polygon*>& polygons, const Ray& ray);

class Camera {
public:
	Camera(int w, int h);

	int getWidth();
	int getHeight();
	glm::vec3 getLocation();
	void saveImage(std::string filename);
	void traceRays(const std::vector<Polygon*>& polygons, const std::vector<Light*>& lights);
	void renderLights(const std::vector<Light*>& lights, Ray& ray, int j, int i);
	void renderPolygons(const std::vector<Polygon*>& polygons, const std::vector<Light*>& lights, const Ray& ray, int i, int j);
	glm::vec3 calculateRayDirection(int i, int j);
	void progressBar(float percent);
	std::vector<std::vector<ColorRGB>> pixels;

private:
	int width;
	int height;
	glm::vec3 location{ -1.0f, 0.0f, 0.0f };
};
