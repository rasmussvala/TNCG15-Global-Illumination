#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Scene.h"
#include "Cube.h"
#include "Light.h"
#include "Polygon.h"
#include "Sphere.h"
#include "Photon.h"
#include "glm/glm.hpp"

struct hitResult
{
  float t;   // At which length (t) we get a hit
  int index; // Index of the closest intersection with all geometries
};

hitResult closestIntersect(const Ray &ray,
                           const std::vector<Geometry *> geometries);

class Camera
{
public:
  Camera(size_t w, size_t h);

  // Save the image as a .ppm file to the specified
  void saveImage(std::string filename);

  // Loop through all the pixels created for the cameras viewports and cast rays
  void castRays(int samplesPerPixel);

  // Cast photons into the scene for the camera rays to catch
  std::vector<Photon> castPhotons(Scene *scene, int photonCount);

  // Adds geometry, light, and configures render settings
  void configure(Scene *newScene, int newDepthDiffuse,
                 int newDepthReflective, int newShadowRays,
                 int newIndirectRays);

private:
  // ----- PHOTON THINGS (PASS 1) -----

  // Calculate the geometric factor (Gm)
  float computeGeometricFactor(const glm::vec3 &sphereCenter, const glm::vec3 &lightCenter);

  // Calculate the projected area (As)
  float computeProjectedArea(float geometricFactor, float sphereRadius);

  void castPhoton(Photon &photon, int scatterDepth);

  // ----- NORMAL RAY STUFF (PASS 2) -----

  // Cast a ray and return the color of that ray
  glm::vec3 castRay(const Ray &ray, int depthDiffuse, int depthReflective);

  // Return the color of the direct light
  glm::vec3 directLight(const glm::vec3 &hitPoint,
                        const glm::vec3 &hitPointNormal, int index);

  // Return the color of the indirect light
  glm::vec3 indirectLight(int depthDiffuse, int depthReflective,
                          const glm::vec3 &hitPoint,
                          const glm::vec3 &hitPointNormal);

  // Calculate the ray direction from the cameras origin to it's viewport
  glm::vec3 rayDirectionFromCamera(int i, int j) const;

  // Calulate a new random ray direction based on the intersection
  glm::vec3 randomRayDirection(const glm::vec3 &hitPointNormal);

  // Print the progress of the render in the console
  void progressBar(float percent);

  // Convert from hemispherical coordinate to world coordinate
  glm::vec3 sphericalToCartesian(float phi, float omega);

  size_t width;
  size_t height;
  glm::vec3 location{-1.0f, 0.0f, 0.0f};

  Scene *scene;
  std::vector<Photon> photons;

  int MAX_DEPTH_DIFFUSE;
  int MAX_DEPTH_REFLECTIVE;
  int MAX_SHADOWRAYS;
  int MAX_INDIRECTRAYS;

  std::vector<glm::vec3> pixels; // Changed to 1D vector

  const float EPSILON = 1e-4f;
  const float PI = 3.14159265f;
};
