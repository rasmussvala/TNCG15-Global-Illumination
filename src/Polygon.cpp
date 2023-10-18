#pragma once

#include "../include/Polygon.h"
#include "../include/glm/glm.hpp"
#include <iostream>

Rectangle::Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const Material& mat)
	: vertex1(p1), vertex2(p2), vertex3(p3), vertex4(p4), material(mat) {
	// Beräkna c1 och c2, som är de två kantvektorerna som utgår från en av hörnen.
	c1 = vertex2 - vertex1;
	c2 = vertex4 - vertex1; 

	// Beräkna normalen N till rektangeln som är c1 × c2.
	normal = glm::normalize(glm::cross(c1, c2));
}

float Rectangle::intersect(const Ray& ray) const {

	Triangle triangle1(vertex1, vertex2, vertex3, material);
	Triangle triangle2(vertex1, vertex3, vertex4, material);

	// Kollar snittet mellan ray och de två trianglarna som utgör rektangeln
	float t1 = triangle1.intersect(ray);
	float t2 = triangle2.intersect(ray);

	const float EPSILON = 1e-4f;

	// Kollar om snittet är större än EPSILON
	if (t1 >= EPSILON && t2 >= EPSILON) {
		return std::min(t1, t2); // Returnerar det minsta snittet
	}
	else if (t1 >= EPSILON) {
		return t1;
	}
	else if (t2 >= EPSILON) {
		return t2;
	}
	else {
		return -FLT_MAX; // Inget snitt
	}
}


Triangle::Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const Material& mat)
	: vertex1(p1), vertex2(p2), vertex3(p3), material(mat) {

	normal = glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex1));
}

float Triangle::intersect(const Ray& ray) const {
	const float EPSILON = 1e-4f;

	glm::vec3 E1 = vertex2 - vertex1;
	glm::vec3 E2 = vertex3 - vertex1;
	glm::vec3 T = ray.getOrigin() - vertex1;
	glm::vec3 D = ray.getDirection();
	glm::vec3 P = glm::cross(D, E2);
	float determinant = glm::dot(P, E1);

	if (std::abs(determinant) < EPSILON) {
		return -FLT_MAX; // Ray is parallel to the triangle.
	}

	float invDeterminant = 1.0f / determinant;

	float u = glm::dot(P, T) * invDeterminant;
	if (u < -EPSILON || u > 1.0f + EPSILON) {
		return -FLT_MAX;
	}

	glm::vec3 Q = glm::cross(T, E1);
	float v = glm::dot(Q, D) * invDeterminant;
	if (v < -EPSILON || u + v > 1.0f + EPSILON) {
		return -FLT_MAX;
	}

	float t = glm::dot(Q, E2) * invDeterminant;
	if (t < EPSILON) {
		return -FLT_MAX; // Intersection point is too close to the ray's origin.
	}

	return t;
}
