#pragma once
#include "glm/glm.hpp"
#include "Ray.h"
#include "ColorRGB.h"
#include "Material.h"

class Polygon {
public:
	virtual float intersect(const Ray& ray) const = 0;
	virtual glm::vec3 getNormal() const = 0;
	virtual Material getMaterial() const = 0;
};

class Rectangle : public Polygon {
public:
	Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const Material& mat);

	float intersect(const Ray& ray) const override;


	glm::vec3 getNormal() const override {
		return normal;
	}

	Material getMaterial() const override {
		return material; 
	}

private:
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;
	glm::vec3 vertex4;
	glm::vec3 normal;
	Material material; 
};



class Triangle : public Polygon {
public:
	Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const Material& mat);

	float intersect(const Ray& ray) const override;
	
	Material getMaterial() const override {
		return material;
	}

	glm::vec3 getNormal() const override {
		return normal;
	}	

private:
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;
	glm::vec3 normal; 
	Material material;
};
