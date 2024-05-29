#pragma once

#include "Ray.h"
#include "glm/glm.hpp"

enum MaterialType { REFLECTIVE, TRANSPARENT, DIFFUSE };

struct Material {
  MaterialType type;
  glm::vec3 color;
  float refractiveIndex;

  // Constructor for MIRROR
  Material(MaterialType t)
      : type(t), color(glm::vec3(0.0, 0.0, 0.0)), refractiveIndex(1.0f) {}

  // Constructor for DIFFUSE
  Material(MaterialType t, glm::vec3 c)
      : type(t), color(c), refractiveIndex(1.0f) {}

  // Constructor for TRANSPARENT
  Material(MaterialType t, float ri)
      : type(t), color(glm::vec3(0.0, 0.0, 0.0)), refractiveIndex(ri) {}
};

class Geometry {
 public:
  virtual ~Geometry() {}

  virtual float intersect(const Ray& ray) const = 0;
  virtual glm::vec3 getNormal(const glm::vec3& point) const = 0;
  virtual Material getMaterial() const = 0;
};
