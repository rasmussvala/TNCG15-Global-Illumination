#pragma once
#include "../include/glm/glm.hpp"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"

// Area light
class Light {
public:
	// räkna ut random point på ljuskällan
	// räkna ut irradiance 
	Light (glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4) : v1(v1), v2(v2), v3(v3), v4(v4) {
		e1 = v2 - v1;
		e2 = v3 - v1; // e2 = v4 - v1 kanske 
		area = glm::length(e1) * glm::length(e2);
		normal = glm::normalize(glm::cross(e1, e2));
	}

	float calculateLight(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal);

private:
	glm::vec3 v1, v2, v3, v4;
	glm::vec3 e1, e2;
	float area;
	glm::vec3 normal;
	float irradiance = 0.0f; // light intensity W/m^2
};
