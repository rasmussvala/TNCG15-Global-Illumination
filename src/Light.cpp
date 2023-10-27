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
    normal = rectangle.getNormal(v1);
}

Rectangle Light::getGeometry() {
    return rectangle;
}

float Light::calculateLight(const std::vector<Geometry*>& geometries, const glm::vec3& hitPoint, const glm::vec3& hitPointNormal, int MAX_SHADOWRAYS) {
    const float EPSILON = 1e-4f;
    float irradiance = 0.0f;
    int N = MAX_SHADOWRAYS; // antal samples
    float Le = 130.0f; // radiance
    const float PI = 3.14159265f;

    for (int i = 0; i < N; i++) {
        // Värde mellan 0 - 1 
        float S = static_cast<float>(rand()) / RAND_MAX;
        float T = static_cast<float>(rand()) / RAND_MAX;

        glm::vec3 pointOnLight = v1 + S * e1 + T * e2; // random point på ljuskälla 
        glm::vec3 direction = pointOnLight - hitPoint; //di 
        glm::vec3 directionNormalized = glm::normalize(direction);
        float distanceToLight = glm::distance(pointOnLight, hitPoint);
        Ray rayToLight(hitPoint, direction);

        IntersectionResult result = closestIntersect(rayToLight, geometries);
        float closestT = result.t;

        // Något finns ivägen för ljuskällan -> skugga 
        if (closestT > EPSILON && closestT < distanceToLight) {
            continue;
        }

        float cosOmegaX = glm::dot(hitPointNormal, directionNormalized);
        float cosOmegaY = glm::dot(-normal, directionNormalized);

        irradiance += std::max(0.0f, (cosOmegaX * cosOmegaY) / (distanceToLight * distanceToLight));
    }

    irradiance = (irradiance * area * Le) / (N * PI);

    return irradiance;
}
