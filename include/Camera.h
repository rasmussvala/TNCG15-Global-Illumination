#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ColorRGB.h"
#include "Cube.h"
#include "Light.h"
#include "Polygon.h"
#include "Sphere.h"
#include "glm/glm.hpp"

struct hitResult {
  float t;
  int index;
};

hitResult closestIntersect(const Ray& ray,
                           const std::vector<Geometry*> geometries);

class Camera {
 public:
  Camera(int w, int h);

  void saveImage(std::string filename);
  void castRays(int samplesPerPixel);
  ColorRGB castRay(const Ray& ray, int depthDiffuse, int depthReflective);
  ColorRGB directLight(const glm::vec3& hitPoint,
                       const glm::vec3& hitPointNormal, int index);
  ColorRGB indirectLight(int depthDiffuse, int depthReflective,
                         const glm::vec3& hitPoint,
                         const glm::vec3& hitPointNormal);
  glm::vec3 rayDirectionFromCamera(int i, int j) const;
  glm::vec3 randomRayDirection(const glm::vec3& hitPointNormal);
  void progressBar(float percent);

  glm::vec3 HemisphericalToLocalCartesian(float phi, float omega);
  glm::vec3 LocalCartesianToWorldCartesian(const glm::vec3& localDir,
                                           const glm::vec3& normal);

  void setGeometries(const std::vector<Geometry*>& newGeometries) {
    geometries = newGeometries;
  }

  void setLights(const std::vector<Light*>& newLights) { lights = newLights; }

  void setDepthDiffuse(const int newDepthDiffuse) {
    MAX_DEPTH_DIFFUSE = newDepthDiffuse;
  }

  void setDepthReflective(const int newDepthReflective) {
    MAX_DEPTH_REFLECTIVE = newDepthReflective;
  }

  void setShadowRays(const int newShadowRays) {
    MAX_SHADOWRAYS = newShadowRays;
  }

  void setIndirectRays(const int newIndirectRays) {
    MAX_INDIRECTRAYS = newIndirectRays;
  }

 private:
  int width;
  int height;
  glm::vec3 location{-1.0f, 0.0f, 0.0f};

  std::vector<Geometry*> geometries;
  std::vector<Light*> lights;

  int MAX_DEPTH_DIFFUSE;
  int MAX_DEPTH_REFLECTIVE;
  int MAX_SHADOWRAYS;
  int MAX_INDIRECTRAYS;

  std::vector<std::vector<ColorRGB>> pixels;

  const float EPSILON = 1e-4f;
  const float PI = 3.14159265f;
};
