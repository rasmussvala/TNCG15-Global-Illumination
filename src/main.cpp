#pragma once

#include "../include/Scene.h"
#include "../include/Polygon.h"
#include "../include/Cube.h"
#include "../include/Sphere.h"

int main() {
	// max 180 x 180 atm
	Scene myScene(600, 600);

	// Default cube gets added to right hand side
	Cube cube1{};
	myScene.addCube(&cube1);

	// Settings for Sphere 
	glm::vec3 center{ 8.0f, 2.5f, -3.5f };
	float radius = 1.5f;
	ColorRGB blue{ 0.0f,0.0f,0.4f };
	Material materialBlue{ REFLECTIVE };

	Sphere sphere1{center, radius, materialBlue};
	myScene.addGeometry(&sphere1);

	Light light1{ glm::vec3{5.0f, 1.0f, 4.9999f},
		glm::vec3{3.0f, 1.0f, 4.9999f},
		glm::vec3{3.0f, -1.0f, 4.9999f},
		glm::vec3{5.0f, -1.0f, 4.9999f}
	};

	myScene.addLight(&light1);

	int depth = 5; // > 1
	int nrOfShadowRays = 1; // > 1
	int nrOfIndirectRays = 1;

	myScene.render(depth, nrOfShadowRays, nrOfIndirectRays);

	return 0;
}

// @TODO - kontrollera ny direction för randomRays
// @TODO - memoryleaks! 
// @TODO - fixa rendering till glas
// @TODO - fixa så att man ser ljuskällan (fixa senare)
// @TODO - fixa antialiasing
// @TODO - tänk på att ytan vända fel kastas bort i traingle::intersect (hur glas ska hantera det) om bool insideObj = true, ignorera? 