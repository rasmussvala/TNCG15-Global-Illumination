#pragma once
#include "../include/glm/glm.hpp"

class Ray {
public:
	Ray(const glm::vec4& orig, const glm::vec4& dir) : origin(orig), direction(dir) {}

	glm::vec4 getOrigin() const { return origin; }
	glm::vec4 getDirection() const { return direction; }

	glm::vec4 at(float t) const {
		return origin + t * direction;
	}
private:
	glm::vec4 origin;
	glm::vec4 direction;
};
