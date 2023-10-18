#pragma once
#include "../include/glm/glm.hpp"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"
#include "../include/Light.h"
#include "../include/Cube.h"
#include "../include/Sphere.h"
#include <fstream>
#include <vector>
#include <string>

enum IntersectionType { POLYGON, SPHERE, NONE };

struct IntersectionResult {
	float t;
	int index;
	IntersectionType type;
};

IntersectionResult findClosestIntersection(const std::vector<Polygon*>& polygons, std::vector<Sphere*> spheres, const Ray& ray);

class Camera {
public:
	Camera(int w, int h);

	void saveImage(std::string filename);
	void castRays(const std::vector<Polygon*>& polygons, std::vector<Sphere*> spheres, const std::vector<Light*>& lights);
	void renderLights(const std::vector<Light*>& lights, Ray& ray, int j, int i);
	void handleIntersection(const std::vector<Polygon*>& polygons, std::vector<Sphere*> spheres, const std::vector<Light*>& lights, const Ray& ray, int i, int j, int depth);
	glm::vec3 calculateRayDirectionFromCamera(int i, int j);
	void progressBar(float percent);
	std::vector<std::vector<ColorRGB>> pixels;

private:
	int width;
	int height;
	glm::vec3 location{ -1.0f, 0.0f, 0.0f };
};
