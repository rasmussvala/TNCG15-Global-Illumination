#pragma once
#include "Polygon.h"
#include "Camera.h"
#include "Light.h"
#include <vector>
#include "Object.h"

class Scene {
public:
    Scene(int width, int height);

    void addPolygon(Polygon* polygon) {
        polygons.push_back(polygon);
    }

    void addLight(Light* light) {
		lights.push_back(light);
	}

    void addObjects(Cube* cude) {
        objects.push_back(cude);
	}

    void render() {
        camera.traceRays(polygons, lights, objects);
        camera.saveImage("../images/test.ppm");
    }

    void HemisphericalToLocalCartesian(double inclination, double azimuth, glm::vec3& cartesian);     
    void LocalCartesianToHemispherical(const glm::vec3& cartesian, double& inclination, double& azimuth);
    void LocalCartesianToWorldCartesian(const glm::vec3& local, const glm::vec3& normal, glm::vec3& world);
    void WorldCartesianToLocalCartesian(const glm::vec3& world, const glm::vec3& normal, glm::vec3& local);

private:
    Camera camera;
    std::vector<Polygon*> polygons;
    std::vector<Light*> lights;
    std::vector<Object*> objects;
};
