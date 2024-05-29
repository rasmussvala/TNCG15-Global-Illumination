#pragma once
#include <vector>

#include "Camera.h"
#include "Cube.h"
#include "Light.h"
#include "Polygon.h"
#include "Sphere.h"

class Scene {
 public:
  Scene(int width, int height);

  void addLight(Light* light);
  void addGeometry(Geometry* geometry);
  void addCube(Cube* cube);
  void render(int diffuseBounceCount, int mirrorBounceCount, int shadowRayCount,
              int indirectRayCount, int raysPerPixel, std::string outputPath);

 private:
  Camera camera;
  std::vector<Geometry*> geometries;
  std::vector<Light*> lights;
};
