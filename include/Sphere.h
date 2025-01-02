#pragma once

#include "Geometry.h"
#include <vector>

class Sphere : public Geometry
{
public:
  Sphere(const glm::vec3 &center, float radius, const Material &material);

  float intersect(const Ray &ray) const override;
  glm::vec3 getNormal(const glm::vec3 &point) const override;
  Material getMaterial() const override;
  GeometryType getGeometryType() const override;
  glm::vec3 getCenter() const;
  float getRadius() const;
  std::vector<glm::vec3> getDiskBasis(const glm::vec3 &diskNormal) const;
  glm::vec3 getRandomPointOnDisk(const glm::vec3 &xL, const glm::vec3 &yL) const;

private:
  glm::vec3 center;
  float radius;
  Material material;

  const float PI = 3.14159265f;
};
