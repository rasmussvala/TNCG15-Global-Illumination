#include "../include/Sphere.h"
#include <limits>

Sphere::Sphere() {
    // center (x0,y0,z0)
    x0 = 5.0f;
    y0 = 0.0f;
    z0 = 0.0f;
    r = 2.0f;
}

glm::vec3 Sphere::getNormal(const glm::vec3& pointOnSphere) {
    glm::vec3 pointCenter = pointOnSphere - glm::vec3(x0, y0, z0);
    glm::vec3 normal = glm::normalize(pointCenter);
    return normal;
}

float Sphere::intersect(const Ray& ray) {
    const float EPSILON = 1e-4;
    glm::vec3 rayToCenter = glm::vec3(x0, y0, z0) - ray.getOrigin();
    float a = glm::dot(ray.getDirection(), ray.getDirection());
    float b = 2.0f * glm::dot(ray.getDirection(), rayToCenter);
    float c = glm::dot(rayToCenter, rayToCenter) - (r * r);
    float discriminant = (b * b) - (4.0f * a * c);

    if (discriminant < 0.0f) {
        return -FLT_MAX; // No intersection
    }

    float t1 = (-b - glm::sqrt(discriminant)) / (2.0f * a);
    float t2 = (-b + glm::sqrt(discriminant)) / (2.0f * a);

    if (t1 >= EPSILON && t2 >= EPSILON) {
        return glm::min(t1, t2);
    }

    if (t1 >= EPSILON) {
        return t1;
    }

    if (t2 >= EPSILON) {
        return t2;
    }

    return -FLT_MAX;
}
