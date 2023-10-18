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
    void render();
    void HemisphericalToLocalCartesian(double inclination, double azimuth, glm::vec3& cartesian);
    void LocalCartesianToHemispherical(const glm::vec3& cartesian, double& inclination, double& azimuth);
    void LocalCartesianToWorldCartesian(const glm::vec3& local, const glm::vec3& normal, glm::vec3& world);
    void WorldCartesianToLocalCartesian(const glm::vec3& world, const glm::vec3& normal, glm::vec3& local);

private:
    Camera camera;
    std::vector<Polygon*> polygons;
    std::vector<Light*> lights;
    std::vector<Sphere*> spheres;
};
