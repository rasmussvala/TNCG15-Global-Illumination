#pragma once
#include "../include/glm/glm.hpp"
#include "../include/Ray.h"

class Polygon {
public:
	virtual bool intersect(const Ray& ray, glm::vec3& intersectionPoint) const = 0;
};

class Rectangle : public Polygon {
public:
	Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4)
		: vertex1(p1), vertex2(p2), vertex3(p3), vertex4(p4) {}

	bool intersect(const Ray& ray, glm::vec3& intersectionPoint) const override {
		// Implement
		glm::vec3 normal = glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex1));
	}

private:
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;
	glm::vec3 vertex4;
};

class Triangle : public Polygon {
public:
	Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
		: vertex1(p1), vertex2(p2), vertex3(p3) {}

	bool intersect(const Ray& ray, glm::vec3& intersectionPoint) const override {
		// Implement
	}

private:
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;
};

