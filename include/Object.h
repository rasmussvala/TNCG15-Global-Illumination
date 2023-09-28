#pragma once

#pragma once
#include "../include/glm/glm.hpp"
#include "../include/Ray.h"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"

class Object {
public:
	virtual float intersect(const Ray& ray) const = 0;
	virtual glm::vec3 getNormal(const glm::vec3& point) const = 0;
	virtual ColorRGB getColor() const = 0;
};

class Cube : public Object {
public:
	float intersect(const Ray& ray) const override;
	glm::vec3 getNormal(const glm::vec3& point) const override { return { 0,0,0 }; }
	ColorRGB getColor() const override { return color; }
private:
	ColorRGB color{ 0.0,0.0,1.0 }; // blue

	glm::vec3 p0{ 5.0f, 3.0f, 0.0f };
	glm::vec3 p1{ 6.0f, 3.0f, 0.0f };
	glm::vec3 p2{ 6.0f, 4.0f, 0.0f };
	glm::vec3 p3{ 5.0f, 4.0f, 0.0f };
	glm::vec3 p4{ 5.0f, 3.0f, 1.0f };
	glm::vec3 p5{ 6.0f, 3.0f, 1.0f };
	glm::vec3 p6{ 6.0f, 4.0f, 1.0f };
	glm::vec3 p7{ 5.0f, 4.0f, 1.0f };

	Rectangle surface1{ p0, p1, p2, p3, color }; // botten
	Rectangle surface2{ p4, p7, p6, p5, color }; // toppen
	Rectangle surface3{ p0, p3, p7, p4, color }; // sidan mot kameran
	Rectangle surface4{ p3, p2, p6, p7, color }; // sidan mot höger
	Rectangle surface5{ p0, p4, p5, p1, color }; // sidan mot vänster
	Rectangle surface6{ p1, p5, p6, p2, color }; // sidan mot bortre väggen
};

class Sphere : public Object {
public:
	float intersect(const Ray& ray) const override { return 0.0f; }
	glm::vec3 getNormal(const glm::vec3& point) const override { return { 0,0,0 }; }
	ColorRGB getColor() const override { return { 0,0,0 }; }
private:

};