#pragma once
#include "Polygon.h"
#include "Camera.h"
#include "Light.h"
#include "Cube.h"
#include "Sphere.h"
#include <vector>

class Scene {
public:
    Scene(int width, int height);

    void addLight(Light* light);
    void addGeometry(Geometry* geometry);
    void addCube(Cube* cube);
    void render(int depthDiffuse, int depthReflective, int nrOfShadowRays, int nrOfIndirectRays, int samplesPerPixel);

private:
    Camera camera;
    std::vector<Geometry*> geometries;
    std::vector<Light*> lights;
};
