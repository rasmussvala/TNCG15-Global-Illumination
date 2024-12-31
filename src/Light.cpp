#include "../include/Light.h"

#include <cstdlib> // for rand function
#include <vector>

#include "../include/Camera.h"
#include "../include/Cube.h"
#include "../include/Sphere.h"
#include "../include/glm/glm.hpp"

Light::Light(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4)
    : v1(v1), v2(v2), v3(v3), v4(v4)
{
  e1 = v2 - v1;
  e2 = v4 - v1;
  area = glm::length(e1) * glm::length(e2);
  normal = rectangle.getNormal(v1);
}

Rectangle Light::getGeometry() { return rectangle; }

float Light::calculateLight(const std::vector<Geometry *> &geometries,
                            const glm::vec3 &hitPoint,
                            const glm::vec3 &hitPointNormal,
                            int MAX_SHADOWRAYS) const
{
  const float EPSILON = 1e-4f;
  float irradiance = 0.0f;
  int N = MAX_SHADOWRAYS; // antal samples
  float Le = 150.0f;      // radiance
  const float PI = 3.14159265f;

  glm::vec3 pointOnLight;
  glm::vec3 direction;

  float S;
  float T;
  float distanceToLight;
  float cosOmegaX;
  float cosOmegaY;

  Ray rayToLight{};

  for (int i = 0; i < N; i++)
  {
    // V�rde mellan 0 - 1
    S = static_cast<float>(rand()) / RAND_MAX;
    T = static_cast<float>(rand()) / RAND_MAX;

    pointOnLight = v1 + S * e1 + T * e2; // random point p� ljusk�lla
    direction = pointOnLight - hitPoint; // di
    distanceToLight = glm::distance(pointOnLight, hitPoint);
    rayToLight.setRay(hitPoint, direction);

    hitResult hit = closestIntersect(rayToLight, geometries);

    // N�got finns iv�gen f�r ljusk�llan -> skugga
    if (hit.t > EPSILON && hit.t < distanceToLight)
    {
      continue;
    }

    cosOmegaX = glm::dot(hitPointNormal, glm::normalize(direction));
    cosOmegaY = glm::dot(-normal, glm::normalize(direction));

    irradiance += std::max(
        0.0f, (cosOmegaX * cosOmegaY) / (distanceToLight * distanceToLight));
  }

  irradiance = (irradiance * area * Le) / (N * PI);

  return irradiance;
}
