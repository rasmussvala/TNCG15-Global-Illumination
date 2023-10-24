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

    void addPolygon(Polygon* polygon);
    void addLight(Light* light);
    void addSphere(Sphere* sphere);
    void addCube(Cube* cube);
    void render(int depth);

private:
    Camera camera;
    std::vector<Polygon*> polygons;
    std::vector<Light*> lights;
    std::vector<Sphere*> spheres;
};
