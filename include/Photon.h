#pragma once

#include "glm/glm.hpp"
#include "Ray.h"

struct Photon
{
    Ray ray;
    float flux;

    Photon(const Ray &ray, float flux) : ray(ray), flux(flux) {}
};
