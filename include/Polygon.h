#pragma once
#include "../include/glm/glm.hpp"
#include "../include/Ray.h"
#include "../include/ColorRGB.h"

class Polygon {
public:
	virtual bool intersect(const Ray& ray, glm::vec3& intersectionPoint) const = 0;
	virtual ColorRGB getColor() const = 0;
};

class Rectangle : public Polygon {
public:
	Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);

	bool intersect(const Ray& ray, glm::vec3& intersectionPoint) const override;
	ColorRGB getColor() const override{
		return color;
	}

private:
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;
	glm::vec3 vertex4;
	ColorRGB color{ 0.0,0.0,0.0 };
};



class Triangle : public Polygon {
public:
	Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const ColorRGB& color);

	bool intersect(const Ray& ray, glm::vec3& intersectionPoint) const override;
	ColorRGB getColor() const override {
		return color;
	}

private:
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;
	ColorRGB color{ 0.0,0.0,0.0 };
};
