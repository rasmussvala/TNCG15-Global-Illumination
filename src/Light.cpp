#include "../include/Light.h"
#include "../include/glm/glm.hpp"

float Light::calculateLight(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal) {
	int N = 100; // antal samples
	float Le = 100.0f; // radiance
	float irradiance = 0.0f;

	for (int i = 0; i < N; i++) {
		// Värde mellan 0 - 1 
		float s = (float)rand() / RAND_MAX;
		float t = (float)rand() / RAND_MAX;

		glm::vec3 y = v1 + s * e1 + t * e2;

		glm::vec3 d = y - intersectionPoint;

		float cosOmegaX = abs(glm::dot(intersectionPointNormal, glm::normalize(d)));
		float cosOmegaY = abs(glm::dot(-normal, glm::normalize(d)));

		irradiance += (cosOmegaX + cosOmegaY) / (glm::length(d) * glm::length(d));
	}

	irradiance = irradiance * area * Le / N;

	return irradiance;
}
