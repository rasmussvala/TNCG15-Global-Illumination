#include "../include/Light.h"
#include "../include/Camera.h"

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

  float distanceToLight;
  float cosOmegaX;
  float cosOmegaY;

  Ray rayToLight{};

  for (int i = 0; i < N; i++)
  {
    glm::vec3 pointOnLight = getRandomPoint(); // random point pa ljuskalla

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

glm::vec3 Light::getRandomPoint() const
{
  float S = static_cast<float>(rand()) / RAND_MAX;
  float T = static_cast<float>(rand()) / RAND_MAX;

  return v1 + S * e1 + T * e2;
}

glm::vec3 Light::getCenter() const
{
  // v1 and v3 are in opposite end (x), we use the diagonal to find the center
  // x---o
  // |   |
  // 0---x

  float x = v1.x + v3.x / 2;
  float y = v1.y + v3.y / 2;
  float z = v1.z + v3.z / 2;

  return glm::vec3(x, y, z);
}
