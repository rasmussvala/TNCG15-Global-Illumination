#include "../include/Polygon.h"

Rectangle::Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4)
	: vertex1(p1), vertex2(p2), vertex3(p3), vertex4(p4) {}

bool Rectangle::intersect(const Ray& ray, glm::vec3& intersectionPoint) const {

	/* -------------------------------------
	*
	* WIP DETTA ÄR ENBART KOD SOM ÄR AUTOGENERERAT 
	*
		-------------------------------------*/

	glm::vec3 normal = glm::normalize(glm::cross(vertex2 - vertex1, vertex3 - vertex1));
	float t = glm::dot(normal, vertex1 - ray.getOrigin()) / glm::dot(normal, ray.getDirection());

	if (t < 0) {
		return false;
	}

	glm::vec3 point = ray.at(t);

	// Check if the point is inside the rectangle
	glm::vec3 v0 = vertex1 - intersectionPoint;
	glm::vec3 v1 = vertex2 - intersectionPoint;
	glm::vec3 v2 = vertex3 - intersectionPoint;
	glm::vec3 v3 = vertex4 - intersectionPoint;

	// Check if the point is on the correct side of all sides
	if (glm::dot(glm::cross(v0, v1), normal) >= 0.0f &&
		glm::dot(glm::cross(v1, v2), normal) >= 0.0f &&
		glm::dot(glm::cross(v2, v3), normal) >= 0.0f &&
		glm::dot(glm::cross(v3, v0), normal) >= 0.0f) {
		// Yes, the point is inside the rectangle
		return true;
	}

	// No, the point is outside the rectangle
	return false;
}

Triangle::Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3)
	: vertex1(p1), vertex2(p2), vertex3(p3) {}

bool Triangle::intersect(const Ray& ray, glm::vec3& intersectionPoint) const {
	// Implement the intersection logic for a triangle here
	return false;
}
