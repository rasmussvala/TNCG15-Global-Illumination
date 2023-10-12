#pragma once
#include "../include/glm/glm.hpp"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"
#include "../include/Ray.h"
#include "../include/Object.h"
#include <vector>

// Area light
class Light {
public:
	Light(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4) : v1(v1), v2(v2), v3(v3), v4(v4) {
		e1 = v2 - v1;
		e2 = v4 - v1;
		area = glm::length(e1) * glm::length(e2);
		normal = glm::normalize(glm::cross(e1, e2));
	}

	Rectangle getGeometry() {
		return rectangle;
	}

	float calculateLight(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, const std::vector<Object*>& objects);

private:
	glm::vec3 v1, v2, v3, v4;
	glm::vec3 e1, e2;
	float area;
	glm::vec3 normal;
	ColorRGB white{ 1.0f, 1.0f ,1.0f };
	Material materialWhite{ white, 0.0, 0.0, 0.0 };
	Rectangle rectangle{ v1, v2, v3, v4, materialWhite };
};
