#pragma once

#include "ColorRGB.h"
#include "Ray.h"
#include "glm/glm.hpp"

enum MaterialType { REFLECTIVE, TRANSPARENT, DIFFUSE, NO_TYPE };

struct Material {
  MaterialType type;
  ColorRGB color;
  float refractiveIndex;

  Material()
      : type(NO_TYPE), color(ColorRGB(0.0, 0.0, 0.0)), refractiveIndex(1.0f) {}

  // Constructor for MIRROR
  Material(MaterialType t)
      : type(t), color(ColorRGB(0.0, 0.0, 0.0)), refractiveIndex(1.0f) {}

  // Constructor for DIFFUSE
  Material(MaterialType t, ColorRGB c)
      : type(t), color(c), refractiveIndex(1.0f) {}

  // Constructor for TRANSPARENT
  Material(MaterialType t, float ri)
      : type(t), color(ColorRGB(0.0, 0.0, 0.0)), refractiveIndex(ri) {}
};

class Geometry {
 public:
  virtual ~Geometry() {}

  virtual float intersect(const Ray& ray) const = 0;
  virtual glm::vec3 getNormal(const glm::vec3& point) const = 0;
  virtual Material getMaterial() const = 0;
};
