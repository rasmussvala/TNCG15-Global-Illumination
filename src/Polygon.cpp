#include "../include/Polygon.h"
#include "../include/glm/glm.hpp"
#include <iostream>

Rectangle::Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const ColorRGB& col)
	: vertex1(p1), vertex2(p2), vertex3(p3), vertex4(p4), color(col) {
	// Beräkna c1 och c2, som är de två kantvektorerna som utgår från en av hörnen.
	c1 = vertex2 - vertex1;
	c2 = vertex3 - vertex1; // Kan vara vertex4 - vertex1 också.

	// Beräkna normalen N till rektangeln som är c1 × c2.
	normal = glm::normalize(glm::cross(c1, c2));
}

float Rectangle::intersect(const Ray& ray) const {

	Triangle triangle1(vertex1, vertex2, vertex3, color);
	Triangle triangle2(vertex1, vertex3, vertex4, color);

	// Call the triangle intersection function for both triangles
	float t1 = triangle1.intersect(ray);
	float t2 = triangle2.intersect(ray);

	const float EPSILON = 1e-6;

	// Check if either triangle intersected the ray and return the closest intersection
	if (t1 >= EPSILON && t2 >= EPSILON) {
		return std::min(t1, t2); // Return the closest intersection
	}
	else if (t1 >= EPSILON) {
		return t1;
	}
	else if (t2 >= EPSILON) {
		return t2;
	}
	else {
		return -1.0f; // No intersection
	}
}


Triangle::Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const ColorRGB& col)
	: vertex1(p1), vertex2(p2), vertex3(p3), color(col) {

	normal = glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex1));
}

float Triangle::intersect(const Ray& ray) const {
	// Möller-Trumbore algoritm f�r att hitta snitt mellan ray och triangel

	const float EPSILON = 1e-4;

	glm::vec3 E1 = vertex2 - vertex1;
	glm::vec3 E2 = vertex3 - vertex1;
	glm::vec3 T = ray.getOrigin() - vertex1;
	glm::vec3 D = ray.getDirection();
	glm::vec3 P = glm::cross(D, E2);
	glm::vec3 Q = glm::cross(T, E1);

	float u = (glm::dot(P, T) / glm::dot(P, E1));
	float v = (glm::dot(Q, D) / glm::dot(P, E1));

	if (u + v > 1.0f || u < EPSILON || v < EPSILON) {// Maybe use EPSILON?
		return -INFINITY;
	}
	float t = (glm::dot(Q, E2) / glm::dot(P, E1));

	if (t < EPSILON) {
		return -INFINITY;
	}

	return t;
}

