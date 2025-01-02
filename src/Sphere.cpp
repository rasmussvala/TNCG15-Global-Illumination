#include "../include/Sphere.h"

#include <limits>

Sphere::Sphere(const glm::vec3 &c, float r, const Material &mat)
    : center(c), radius(r), material(mat) {}

float Sphere::intersect(const Ray &ray) const
{
  const float EPSILON = 1e-4f;

  glm::vec3 D = glm::normalize(ray.getDirection());
  glm::vec3 S = ray.getOrigin();
  glm::vec3 C = center;

  // Coefficients for the quadratic equation
  float c1 = glm::dot(D, D);
  float c2 = glm::dot(2.0f * D, S - C);
  float c3 = glm::dot((S - C), (S - C)) - (radius * radius);

  // Calculate the discriminant
  float arg = c2 * c2 - 4.0f * c1 * c3;

  if (arg < 0.0f)
  {
    // No intersection
    return -1.0f;
  }
  else
  {
    // Two possible intersection points
    float t1 = (-c2 - sqrt(arg)) / (2 * c1);
    float t2 = (-c2 + sqrt(arg)) / (2 * c1);

    if (t1 > EPSILON && t2 > EPSILON)
    {
      return glm::min(t1, t2);
    }
    else if (t1 > EPSILON)
    {
      return t1;
    }
    else if (t2 > EPSILON)
    {
      return t2;
    }
    else
    {
      // No valid intersection
      return -1.0f;
    }
  }
}

glm::vec3 Sphere::getNormal(const glm::vec3 &point) const
{
  glm::vec3 normal = glm::normalize(point - center);
  return normal;
}

Material Sphere::getMaterial() const { return material; }

GeometryType Sphere::getGeometryType() const { return GeometryType::SPHERE; }

glm::vec3 Sphere::getCenter() const { return center; }

float Sphere::getRadius() const { return radius; }

std::vector<glm::vec3> Sphere::getDiskBasis(const glm::vec3 &diskNormal) const
{
  // L = local axis, W = world axis
  glm::vec3 zL = diskNormal;
  glm::vec3 xW(1.0f, 0.0f, 0.0f);
  glm::vec3 yL = glm::normalize(glm::cross(zL, xW));
  glm::vec3 xL = glm::normalize(glm::cross(yL, zL));

  return {xL, yL, zL};
}

glm::vec3 Sphere::getRandomPointOnDisk(const glm::vec3 &xL, const glm::vec3 &yL) const
{
  float randomRadius = static_cast<float>(rand()) / RAND_MAX * radius;
  float randomAngle = static_cast<float>(rand()) / RAND_MAX * 2 * PI;

  float a = randomRadius * glm::cos(randomAngle);
  float b = randomRadius * glm::sin(randomAngle);

  glm::vec3 randomPoint = center + a * xL + b * yL;

  return randomPoint;
}