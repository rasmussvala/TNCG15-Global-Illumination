#pragma once

#include "../include/Scene.h"
#include "../include/Polygon.h"
#include "../include/Cube.h"
#include "../include/Sphere.h"

int main() {
	Scene myScene(200, 200);

	Cube cube1{};
	myScene.addCube(&cube1);

	Sphere sphere1{};
	myScene.addSphere(&sphere1);

	Light light1{ glm::vec3{5.0f, 1.0f, 4.9999f},
		glm::vec3{3.0f, 1.0f, 4.9999f},
		glm::vec3{3.0f, -1.0f, 4.9999f},
		glm::vec3{5.0f, -1.0f, 4.9999f}
	};

	myScene.addLight(&light1);

	myScene.render(); 

	return 0;
}

// @TODO - fixa svarta prickar i rectanglar 
// @TODO - fixa så att man ser ljuskällan
// @TODO - fixa antialiasing
// @TODO - fixa MC
// @TODO - fixa rendering till glas