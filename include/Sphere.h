#pragma once

#include "../include/glm/glm.hpp"
#include "../include/Ray.h"

class Sphere
{
public:
    Sphere();

    glm::vec3 getNormal(const glm::vec3& pointOnSphere);
    float intersect(const Ray& ray);

private:
    float x0, y0, z0, r;
};
