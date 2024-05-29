#pragma once

#include <vector>

#include "ColorRGB.h"
#include "Cube.h"
#include "Geometry.h"
#include "Polygon.h"
#include "Ray.h"
#include "Sphere.h"
#include "glm/glm.hpp"

// Area light
class Light {
 public:
  Light(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4);

  Rectangle getGeometry();
  float calculateLight(const std::vector<Geometry*>& geometries,
                       const glm::vec3& intersectionPoint,
                       const glm::vec3& intersectionPointNormal,
                       int MAX_SHADOWRAYS);

 private:
  glm::vec3 v1, v2, v3, v4;
  glm::vec3 e1, e2;
  float area;
  glm::vec3 normal;
  ColorRGB white{1.0f, 1.0f, 1.0f};
  Material materialWhite{DIFFUSE, white};
  Rectangle rectangle{v1, v2, v3, v4, materialWhite};
};
