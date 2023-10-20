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
	void castRay(const Ray& ray, int depth, ColorRGB& color);
	void handleTransparent(const Ray& ray, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, const Material& glassMaterial, int depth);
	void handleReflection(const Ray& ray, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, int depth, ColorRGB& color);
	void handleDiffuse(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, IntersectionType type, int index, int depth, ColorRGB& color);
	glm::vec3 rayDirectionFromCamera(int i, int j);
	glm::vec3 randomRayDirection(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal);
	void progressBar(float percent);
	std::vector<std::vector<ColorRGB>> pixels;

	static inline glm::vec3 HemisphericalToLocalCartesian(double phi, double omega);
	static inline glm::vec3 LocalCartesianToWorldCartesian(const glm::vec3& local, const glm::vec3& normal);

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
