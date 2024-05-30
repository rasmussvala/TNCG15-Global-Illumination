#pragma once

#include "../include/Cube.h"
#include "../include/Polygon.h"
#include "../include/Scene.h"
#include "../include/Sphere.h"

int main() {
  // 400x400 pixels is max on my pc with low settings
  Scene myScene(100, 100);

  // Default cube adds a blue cube to right hand side
  Cube cube1{};
  myScene.addCube(&cube1);

  // Create a sphere
  glm::vec3 center{8.0f, 2.5f, -3.5f};
  float radius = 1.5f;
  Material material{REFLECTIVE};
  Sphere sphere{center, radius, material};
  myScene.addGeometry(&sphere);

  // Create a rectangular light with a position just below the roof
  Light light{glm::vec3{5.0f, 1.0f, 4.9999f}, glm::vec3{5.0f, -1.0f, 4.99999f},
              glm::vec3{3.0f, -1.0f, 4.9999f}, glm::vec3{3.0f, 1.0f, 4.9999f}};
  myScene.addLight(&light);

  // ----- Parameters to change -----

  // Determines the number of bounces on diffuse objects, recommends 2
  int diffuseBounceCount = 2;

  // Determines the number of bounces on mirrors, recommends 5 for
  // mirror-in-mirror effect
  int mirrorBounceCount = 5;

  // Determines the number of shadow rays to shoot at each light source in the
  // scene. Mark recommends 100, but I suggest a max of 10
  int shadowRayCount = 10;

  // Determines the number of rays to create when hitting a diffuse object
  int indirectRayCount = 1;

  // Determines the number of rays shot from a single pixel, then averages them
  // Demanding!
  int raysPerPixel = 1;

  myScene.render(diffuseBounceCount, mirrorBounceCount, shadowRayCount,
                 indirectRayCount, raysPerPixel, "../images");

  return 0;
}

// TODO: memoryleaks!
// TODO: Kolla hur färger blandas - direktljus och indirektljus
// TODO: fixa rendering till glas
// TODO: tänk på att ytan vända fel kastas bort i traingle::intersect (hur
// glas ska hantera det) om bool insideObj = true, ignorera?
// TODO: fixa så att man ser ljuskällan (fixa senare)
