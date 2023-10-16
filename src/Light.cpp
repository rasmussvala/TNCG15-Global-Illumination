#include "../include/Light.h"
#include "../include/glm/glm.hpp"
#include "../include/Cube.h"
#include <vector>

float Light::calculateLight(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, const std::vector<Polygon*>& polygons) {
	int N = 10; // antal samples
	float Le = 10.0f; // radiance
	float irradiance = 0.0f;
	const float EPSILON = 10e-6;

	// Lambertian reflectors: f(x, di, theta0) = 1 / pi

	for (int i = 0; i < N; i++) {
		// Värde mellan 0 - 1 
		float S = (float)rand() / RAND_MAX;
		float T = (float)rand() / RAND_MAX;

		glm::vec3 pointOnLight = v1 + S * e1 + T * e2; // random point på ljuskälla 

		glm::vec3 direction = pointOnLight - intersectionPoint; // direction

		float distanceToLight = glm::distance(pointOnLight, intersectionPoint);

		Ray rayToLight(intersectionPoint, direction);

		float smallestT = FLT_MAX;
		std::vector<float> t_values{};

		// Kollar igenom alla polygons, och hittar alla snitt
		for (const auto& poly : polygons) {
			t_values.push_back(poly->intersect(rayToLight));
		}

		// Ansätter det närmaste snittet 
		for (int i = 0; i < t_values.size(); i++) {
			if (t_values[i] > EPSILON && t_values[i] < smallestT) {
				smallestT = t_values[i];
			}
		}

		// Något finns ivägen för ljuskällan -> skugga 
		/*if (smallestT > EPSILON && smallestT < distanceToLight) {
			return 0.0f;
		}*/

		float cosOmegaX = abs(glm::dot(intersectionPointNormal, glm::normalize(direction)));
		float cosOmegaY = abs(glm::dot(-normal, glm::normalize(direction)));

		irradiance += std::min(1.0f, (cosOmegaX + cosOmegaY) / (glm::length(direction) * glm::length(direction)));
	}

	irradiance = irradiance * area * Le / N;

	return irradiance;
}
