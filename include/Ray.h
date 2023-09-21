#pragma once
#include "../include/glm/glm.hpp"

class Ray {
public:
	Ray(const glm::vec3& orig, const glm::vec3& dir) : origin(orig), direction(dir) {}

	glm::vec3 getOrigin() const { return origin; }
	glm::vec3 getDirection() const { return direction; }

	glm::vec3 at(float t) const {
		return origin + t * direction;
	}

	glm::vec3 intersectionPoint{ 0.0f, 0.0f, 0.0f };

private:
	glm::vec3 origin;
	glm::vec3 direction;
};
