#pragma once

#include "../include/Scene.h"
#include "../include/Polygon.h"
#include "../include/Cube.h"
#include "../include/Sphere.h"

int main() {
	Scene myScene(150, 150);

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

	int depth = 4; 
	myScene.render(depth); 

	return 0;
}

// @TODO - fixa MC: flera rays per pixel, studs på diffusa ytor 
// @TODO - skulle kunna fixa så att MC på diffust är mer baserat på ingångsvectorn 
// @TODO - fixa rendering till glas
// @TODO - fixa så att man ser ljuskällan (fixa senare)
// @TODO - fixa antialiasing
// @TODO - tänk på att ytan vända fel kastas bort i traingle::intersect (hur glas ska hantera det) om bool insideObj = true, ignorera? 