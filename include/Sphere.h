#pragma once

#include "glm/glm.hpp"
#include "Ray.h"
#include "ColorRGB.h"
#include "Material.h"

class Sphere
{
public:
    Sphere();

    glm::vec3 getNormal(const glm::vec3& pointOnSphere);
    float intersect(const Ray& ray);
    Material getMaterial();

private:
    float x0, y0, z0, r;
    ColorRGB blue{ 0.0f, 0.0f, 0.4f };
    Material material{ REFLECTIVE };
    glm::vec3 sphereOrigin;
};
