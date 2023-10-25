#pragma once

#include "../include/Scene.h"
#include "../include/Polygon.h"
#include "../include/Cube.h"
#include "../include/Sphere.h"

int main() {
	// 150 x 150 �r max atm
	Scene myScene(170, 170);

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

	int depth = 3; 
	int nrOfShadowRays = 3; 
	int nrOfIndirectRays = 0;

	myScene.render(depth, nrOfShadowRays, nrOfIndirectRays);

	return 0;
}

// @TODO - kontrollera ny direction f�r randomRays
// @TODO - memoryleaks! 
// @TODO - fixa rendering till glas
// @TODO - fixa s� att man ser ljusk�llan (fixa senare)
// @TODO - fixa antialiasing
// @TODO - t�nk p� att ytan v�nda fel kastas bort i traingle::intersect (hur glas ska hantera det) om bool insideObj = true, ignorera? 