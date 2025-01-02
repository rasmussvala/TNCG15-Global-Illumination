#pragma once

#include "Geometry.h"

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

private:
  glm::vec3 center;
  float radius;
  Material material;
};
