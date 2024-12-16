#pragma once

#include "../include/glm/glm.hpp"

struct Photon
{
    glm::vec3 position;
    glm::vec3 direction;
    float flux;

    Photon(const glm::vec3 &p, const glm::vec3 &d, float f) : position(p), direction(d), flux(f) {}
};
