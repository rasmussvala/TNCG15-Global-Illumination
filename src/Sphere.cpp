#include "../include/Sphere.h"

#include <limits>

#include "../include/Sphere.h"

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
