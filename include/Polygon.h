#pragma once
#include "../include/glm/glm.hpp"
#include "../include/Ray.h"
#include "../include/ColorRGB.h"

class Polygon {
public:
	virtual float intersect(const Ray& ray) = 0;
	virtual ColorRGB getColor() const = 0;
	virtual glm::vec3 getNormal() const = 0;
};

class Rectangle : public Polygon {
public:
	Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const ColorRGB& col);

	float intersect(const Ray& ray) override;

	ColorRGB getColor() const override {
		return color;
	}

	glm::vec3 getNormal() const {
		return normal;
	}

private:
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;
	glm::vec3 vertex4;
	glm::vec3 normal;
	glm::vec3 c1, c2;
	ColorRGB color{ 0.0,0.0,0.0 };
};



class Triangle : public Polygon {
public:
	Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const ColorRGB& color);

	float intersect(const Ray& ray) override;
	ColorRGB getColor() const override {
		return color;
	}

	glm::vec3 getNormal() const {
		return normal;
	}	

private:
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;
	glm::vec3 normal; 
	ColorRGB color{ 0.0,0.0,0.0 };
};
