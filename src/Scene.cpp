#include "../include/Scene.h"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"
#include "../include/Camera.h"

Scene::Scene(int width, int height) : camera(width, height) {
    // Initialization code for the Scene constructor goes here
}

void Scene::addPolygon(Polygon* polygon) {
    polygons.push_back(polygon);
}

void Scene::addLight(Light* light) {
    lights.push_back(light);
}

void Scene::addSphere(Sphere* sphere) {
    spheres.push_back(sphere);
}

void Scene::addCube(Cube* cube) {
    std::vector<Polygon*> surfaces = cube->getSurfaces();
    for (Polygon* surface : surfaces) {
        polygons.push_back(surface);
    }
}

void Scene::render() {
    camera.castRays(polygons, spheres, lights);
    camera.saveImage("../images/test.ppm");
}

void Scene::HemisphericalToLocalCartesian(double phi, double omega, glm::vec3& cartesian) {
    // Implementation for HemisphericalToLocalCartesian
}

void Scene::LocalCartesianToWorldCartesian(const glm::vec3& local, const glm::vec3& normal, glm::vec3& world) {
    // Implementation for LocalCartesianToWorldCartesian
}

void Scene::LocalCartesianToHemispherical(const glm::vec3& cartesian, double& inclination, double& azimuth) {
    // Implementation for LocalCartesianToHemispherical
}

void Scene::WorldCartesianToLocalCartesian(const glm::vec3& world, const glm::vec3& normal, glm::vec3& local) {
    // Implementation for WorldCartesianToLocalCartesian
}
