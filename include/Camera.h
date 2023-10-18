#pragma once
#include "glm/glm.hpp"
#include "ColorRGB.h"
#include "Polygon.h"
#include "Light.h"
#include "Cube.h"
#include "Sphere.h"
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
	void handleIntersection(const std::vector<Polygon*>& polygons, std::vector<Sphere*> spheres, const std::vector<Light*>& lights, const Ray& ray, int i, int j, int depth);
	void handleReflection(const std::vector<Polygon*>& polygons, std::vector<Sphere*> spheres, const std::vector<Light*>& lights, const Ray& ray, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, int i, int j, int depth);
	void handleDiffuse(const std::vector<Polygon*>& polygons, std::vector<Sphere*> spheres, const std::vector<Light*>& lights, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, IntersectionType type, int index, int i, int j);
	glm::vec3 calculateRayDirectionFromCamera(int i, int j);
	void progressBar(float percent);
	std::vector<std::vector<ColorRGB>> pixels;

private:
	int width;
	int height;
	glm::vec3 location{ -1.0f, 0.0f, 0.0f };
};
