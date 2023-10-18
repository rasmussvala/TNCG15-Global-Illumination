#pragma once

#include "../include/Scene.h"
#include "../include/Polygon.h"
#include "../include/Cube.h"
#include "../include/Sphere.h"

int main() {
	Scene myScene(200, 200);

	// Default-konstruktor l�gger till en liten bl� kub och en sf�r i (5,0,2); 
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

// @TODO - Kolla varf�r scenen �r flippad vertikalt
// @TODO - Kolla varf�r scenen inte kan skrivas i konstruktorn
// @TODO - Polygons kan ibland f� snitt i sig sj�lv n�r shadow rays castas 