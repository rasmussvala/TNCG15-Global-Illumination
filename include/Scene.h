#pragma once
#include "Polygon.h"
#include "Camera.h"
#include "Light.h"
#include <vector>

class Scene {
public:
    Scene(int width, int height);

    void addPolygon(Polygon* polygon) {
        objects.push_back(polygon);
    }

    void addLight(Light* light) {
		lights.push_back(light);
	}

    void render() {
        camera.traceRays(objects);
        camera.saveImage("../images/test.ppm");
    }

private:
    Camera camera;
    std::vector<Polygon*> objects;
    std::vector<Light*> lights;
};
