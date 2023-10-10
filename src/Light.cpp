#include "../include/Light.h"
#include "../include/glm/glm.hpp"
#include "../include/Object.h"
#include <vector>

float Light::calculateLight(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, const std::vector<Object*>& objects) {
	int N = 10; // antal samples
	float Le = 10.0f; // radiance
	float irradiance = 0.0f;

	// Lambertian reflectors: f(x, di, theta0) = 1 / pi

	for (int i = 0; i < N; i++) {
		// Värde mellan 0 - 1 
		float s = (float)rand() / RAND_MAX;
		float t = (float)rand() / RAND_MAX;

		glm::vec3 y = v1 + s * e1 + t * e2; // random point on light source

		glm::vec3 d = y - intersectionPoint; // direction

		Ray ray(intersectionPoint, d);

		for (const auto& obj : objects) {
			float T = obj->intersect(ray);
			if (T > 0) {
				return 0.0f;
			}
		}

		float cosOmegaX = abs(glm::dot(intersectionPointNormal, glm::normalize(d)));
		float cosOmegaY = abs(glm::dot(-normal, glm::normalize(d)));

		irradiance += std::min(1.0f, (cosOmegaX + cosOmegaY) / (glm::length(d) * glm::length(d)));
	}

	irradiance = irradiance * area * Le / N;

	return irradiance;
}
