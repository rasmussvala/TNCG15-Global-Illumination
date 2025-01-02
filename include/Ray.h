#pragma once
#include "glm/glm.hpp"

class Ray
{
public:
  Ray()
      : position(glm::vec3(0.0f, 0.0f, 0.0f)),
        direction(glm::vec3(1.0f, 0.0f, 0.0f)) {}

  Ray(const glm::vec3 &orig, const glm::vec3 &dir)
      : position(orig), direction(glm::normalize(dir)) {}

  glm::vec3 getPosition() const { return position; }
  glm::vec3 getDirection() const { return glm::normalize(direction); }

  // Member function to set ray properties
  void setRay(const glm::vec3 &pos, const glm::vec3 &dir)
  {
    position = pos;
    direction = dir;
  }

  glm::vec3 at(float t) const { return position + t * direction; }

private:
  glm::vec3 position;
  glm::vec3 direction;
};
