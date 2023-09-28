#include "../include/Object.h"
#include <vector>

float Cube::intersect(const Ray& ray) const {
    const float EPSILON = 1e-6;

    std::vector<float> t_values = {
        surface1.intersect(ray),
        surface2.intersect(ray),
        surface3.intersect(ray),
        surface4.intersect(ray),
        surface5.intersect(ray),
        surface6.intersect(ray)
    };

    float smallestT = std::numeric_limits<float>::infinity();

    for (float t : t_values) {
        if (t > EPSILON && t < smallestT) {
            smallestT = t;
        }
    }

    if (smallestT == std::numeric_limits<float>::infinity()) {
        return -std::numeric_limits<float>::infinity(); // No intersection
    }

    return smallestT;
}

