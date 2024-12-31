#pragma once
#include <vector>

#include "Cube.h"
#include "Light.h"
#include "Polygon.h"
#include "Sphere.h"

class Camera;

class Scene
{
public:
  Scene(int width, int height);

  void addLight(Light *light);
  void addGeometry(Geometry *geometry);
  const std::vector<Geometry *> &getGeometries() const { return geometries; }
  const std::vector<Light *> &getLights() const { return lights; }
  void addCube(Cube *cube);
  void render(int diffuseBounceCount, int mirrorBounceCount,
              int shadowRayCount, int indirectRayCount, int raysPerPixel,
              std::string outputPath = "..");

private:
  Camera *camera;
  std::vector<Geometry *> geometries;
  std::vector<Light *> lights;
};
