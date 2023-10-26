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
#include <iostream>

enum IntersectionType { POLYGON, SPHERE, NONE };

struct IntersectionResult {
	float t;
	int index;
	IntersectionType type;
};

IntersectionResult closestIntersect(const Ray& ray, const std::vector<Polygon*>& polygons, const std::vector<Sphere*> spheres);

class Camera {
public:
	Camera(int w, int h);

	void saveImage(std::string filename);
	void castRays();
	ColorRGB castRay(const Ray& ray, int depth);
	ColorRGB handleReflection(const Ray& ray, const glm::vec3& intersectPt, const glm::vec3& intersectPtNormal, int depth);
	ColorRGB directLight(const glm::vec3& intersectPt, const glm::vec3& intersectPtNormal, IntersectionType type, int index);
	ColorRGB indirectLight(int depth, const glm::vec3& intersectPt, const glm::vec3& intersectPtNormal);
	glm::vec3 rayDirectionFromCamera(int i, int j);
	glm::vec3 randomRayDirection(const glm::vec3& intersectPtNormal);
	void progressBar(float percent);

	glm::vec3 HemisphericalToLocalCartesian(float phi, float omega);
	glm::vec3 LocalCartesianToWorldCartesian(const glm::vec3& localDir, const glm::vec3& normal);

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

	void setShadowRays(const int newShadowRays) {
		MAX_SHADOWRAYS = newShadowRays;
	}

	void setIndirectRays(const int newIndirectRays) {
		MAX_INDIRECTRAYS = newIndirectRays;
	}

private:
	int width;
	int height;
	glm::vec3 location{ -1.0f, 0.0f, 0.0f };

	std::vector<Polygon*> polygons;
	std::vector<Sphere*> spheres;
	std::vector<Light*> lights;

	int MAX_DEPTH;
	int MAX_SHADOWRAYS;
	int MAX_INDIRECTRAYS;
	
	std::vector<std::vector<ColorRGB>> pixels;
};
