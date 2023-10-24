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

IntersectionResult closestIntersection(const Ray& ray, const std::vector<Polygon*>& polygons, const std::vector<Sphere*> spheres);

class Camera {
public:
	Camera(int w, int h);

	void saveImage(std::string filename);
	void castRays();
	ColorRGB castRay(const Ray& ray, int depth);
	// void handleTransparent(const Ray& ray, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, const Material& glassMaterial, int depth);
	ColorRGB handleReflection(const Ray& ray, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, int depth);
	ColorRGB directLight(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, IntersectionType type, int index, int depth);
	ColorRGB indirectLight(int depth, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal);
	glm::vec3 rayDirectionFromCamera(int i, int j);
	glm::vec3 randomRayDirection(const glm::vec3& intersectionPointNormal);
	void progressBar(float percent);
	std::vector<std::vector<ColorRGB>> pixels;

	glm::vec3 HemisphericalToLocalCartesian(float phi, float omega);
	glm::vec3 LocalCartesianToWorldCartesian(const glm::vec3& local, const glm::vec3& normal);

	void setPolygons(const std::vector<Polygon*>& newPolygons) {
		polygons = newPolygons;
	}

	void setSpheres(const std::vector<Sphere*>& newSpheres) {
		spheres = newSpheres;
	}

	void setLights(const std::vector<Light*>& newLights) {
		lights = newLights;
	}

	void setDepth(const int newDepth) {
		MAX_DEPTH = newDepth;
	}

private:
	int width;
	int height;
	glm::vec3 location{ -1.0f, 0.0f, 0.0f };

	std::vector<Polygon*> polygons;
	std::vector<Sphere*> spheres;
	std::vector<Light*> lights;

	int MAX_DEPTH;
};
