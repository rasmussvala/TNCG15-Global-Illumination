#pragma once
#include "glm/glm.hpp"
#include "Ray.h"
#include "ColorRGB.h"
#include "Polygon.h"
#include "Geometry.h"
#include <vector>

class Cube {
public:
    Cube(); // Declare the constructor
    Material getMaterial() const;
    std::vector<Geometry*> getSurfaces();
private:
    ColorRGB color;
    Material material;

    glm::vec3 p0;
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;
    glm::vec3 p4;
    glm::vec3 p5;
    glm::vec3 p6;
    glm::vec3 p7;

    Rectangle surface1;
    Rectangle surface2;
    Rectangle surface3;
    Rectangle surface4;
    Rectangle surface5;
    Rectangle surface6;
};
