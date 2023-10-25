#pragma once

#include "../include/Light.h"
#include "../include/glm/glm.hpp"
#include "../include/Cube.h"
#include "../include/Camera.h"
#include "../include/Sphere.h"
#include <vector>
#include <cstdlib>  // for rand function

Light::Light(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4) : v1(v1), v2(v2), v3(v3), v4(v4) {
    e1 = v2 - v1;
    e2 = v4 - v1;
    area = glm::length(e1) * glm::length(e2);
    normal = glm::normalize(glm::cross(e1, e2));
}

Rectangle Light::getGeometry() {
    return rectangle;
}

float Light::calculateLight(const std::vector<Polygon*>& polygons, std::vector<Sphere*> spheres, const glm::vec3& intersectionPoint, const glm::vec3& intersectionPointNormal) {
    int N = 3; // antal samples
    float Le = 3200.0f; // radiance
    float irradiance = 0.0f;
    const float EPSILON = 1e-4f;
    const float PI = 3.14159265f;

    // Lambertian reflectors: f(x, di, theta0) = 1 / pi

    for (int i = 0; i < N; i++) {
        // Värde mellan 0 - 1 
        float S = static_cast<float>(rand()) / RAND_MAX;
        float T = static_cast<float>(rand()) / RAND_MAX;

        glm::vec3 pointOnLight = v1 + S * e1 + T * e2; // random point på ljuskälla 
        glm::vec3 direction = glm::normalize(pointOnLight - intersectionPoint);
        float distanceToLight = glm::distance(pointOnLight, intersectionPoint);
        Ray rayToLight(intersectionPoint, direction);

        IntersectionResult result = closestIntersection(rayToLight, polygons, spheres);
        float closestT = result.t;

        // Något finns ivägen för ljuskällan -> skugga 
        if (closestT > EPSILON && closestT < distanceToLight) {
            continue;
        }

        float cosOmegaX = std::abs(glm::dot(intersectionPointNormal, glm::normalize(direction)));
        float cosOmegaY = std::abs(glm::dot(-normal, glm::normalize(direction)));

        irradiance += (cosOmegaX + cosOmegaY) / (glm::length(direction) * glm::length(direction));
    }

    irradiance = (irradiance * area * Le) / (N * PI);

    return irradiance;
}
