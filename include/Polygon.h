#pragma once
#include "../include/glm/glm.hpp"
#include "../include/Ray.h"

class Polygon {
public:
	virtual bool intersect(const Ray& ray, glm::vec4& intersectionPoint) const = 0;
};

class Rectangle : public Polygon {
public:
	Rectangle(const glm::vec4& p1, const glm::vec4& p2, const glm::vec4& p3, const glm::vec4& p4)
		: vertex1(p1), vertex2(p2), vertex3(p3), vertex4(p4) {}

	bool intersect(const Ray& ray, glm::vec4& intersectionPoint) const override {
		// Implement
	}

private:
	glm::vec4 vertex1;
	glm::vec4 vertex2;
	glm::vec4 vertex3;
	glm::vec4 vertex4;
};

class Triangle : public Polygon {
public:
	Triangle(const glm::vec4& p1, const glm::vec4& p2, const glm::vec4& p3)
		: vertex1(p1), vertex2(p2), vertex3(p3) {}

	bool intersect(const Ray& ray, glm::vec4& intersectionPoint) const override {
		// Implement
	}

private:
	glm::vec4 vertex1;
	glm::vec4 vertex2;
	glm::vec4 vertex3;
};

