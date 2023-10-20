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

IntersectionResult findClosestIntersection(const Ray& ray, const std::vector<Polygon*>& polygons, const std::vector<Sphere*> spheres);

class Camera {
public:
	Camera(int w, int h);

	void saveImage(std::string filename);
	void castRays();
	void handleIntersection(const Ray& ray, int i, int j, int depth);
	void handleTransparent(const Ray& ray, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, const Material& glassMaterial, int depth);
	void handleReflection(const Ray& ray, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, int i, int j, int depth);
	void handleDiffuse(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, IntersectionType type, int index, int i, int j);
	glm::vec3 calculateRayDirectionFromCamera(int i, int j);
	void progressBar(float percent);
	std::vector<std::vector<ColorRGB>> pixels;

	void setPolygons(const std::vector<Polygon*>& polygons) {
		this->polygons = polygons;
	}

	void setSpheres(const std::vector<Sphere*>& spheres) {
		this->spheres = spheres;
	}

	void setLights(const std::vector<Light*>& lights) {
		this->lights = lights;
	}

private:
	int width;
	int height;
	glm::vec3 location{ -1.0f, 0.0f, 0.0f };

	std::vector<Polygon*> polygons;
	std::vector<Sphere*> spheres;
	std::vector<Light*> lights;
};
