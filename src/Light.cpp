#include "../include/Light.h"
#include "../include/glm/glm.hpp"
#include "../include/Cube.h"
#include "../include/Camera.h"
#include <vector>

float Light::calculateLight(const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal, const std::vector<Polygon*>& polygons) {
	int N = 5; // antal samples
	float Le = 3200.0f; // radiance
	float irradiance = 0.0f;
	const float EPSILON = 10e-4;
	const float PI = 3.14159265f;

	// Lambertian reflectors: f(x, di, theta0) = 1 / pi

	for (int i = 0; i < N; i++) {
		// Värde mellan 0 - 1 
		float S = (float)rand() / RAND_MAX;
		float T = (float)rand() / RAND_MAX;

		glm::vec3 pointOnLight = v1 + S * e1 + T * e2; // random point på ljuskälla 
		glm::vec3 direction = glm::normalize(pointOnLight - intersectionPoint);
		float distanceToLight = glm::distance(pointOnLight, intersectionPoint);
		Ray rayToLight(intersectionPoint, direction);

		// En struct som sparar kortaste avståndet och dess index i polygon-listan 
		IntersectionResult result = findSmallestTAndIndex(polygons, rayToLight);
		float smallestT = result.smallestT;

		// Något finns ivägen för ljuskällan -> skugga 
		if (smallestT > EPSILON && smallestT < distanceToLight) {
			continue;
		}

		float cosOmegaX = abs(glm::dot(intersectionPointNormal, glm::normalize(direction)));
		float cosOmegaY = abs(glm::dot(-normal, glm::normalize(direction)));

		irradiance += (cosOmegaX + cosOmegaY) / (glm::length(direction) * glm::length(direction));
	}

	irradiance = (irradiance * area * Le) / (N * PI);

	return irradiance;
}
