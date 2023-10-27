#pragma once

#include "../include/Scene.h"
#include "../include/Polygon.h"
#include "../include/Cube.h"
#include "../include/Sphere.h"

int main() {
	Scene myScene(300, 300);

	// Default cube adds a blue cube to right hand side
	Cube cube1{};
	myScene.addCube(&cube1);

	// Settings for Sphere 
	glm::vec3 center{ 8.0f, 2.5f, -3.5f };
	float radius = 1.5f;
	ColorRGB blue{ 0.0f, 0.0f, 0.4f };
	Material materialBlue{ REFLECTIVE };

	Sphere sphere1{center, radius, materialBlue};
	myScene.addGeometry(&sphere1);

	Light light1{ glm::vec3{5.0f, 1.0f, 4.9f},
		glm::vec3{5.0f, -1.0f, 4.9f},
		glm::vec3{3.0f, -1.0f, 4.9f},
		glm::vec3{3.0f, 1.0f, 4.9f}
	};

	myScene.addLight(&light1);

	int depthDiffuse = 2; // > 1
	int depthReflective = 5; // > 1
	int nrOfShadowRays = 5; // > 1
	int nrOfIndirectRays = 3;
	int samplesPerPixel = 2;

	myScene.render(depthDiffuse, depthReflective, nrOfShadowRays, nrOfIndirectRays, samplesPerPixel);

	return 0;
}

// @TODO - memoryleaks! 
// @TODO - fixa rendering till glas
// @TODO - tänk på att ytan vända fel kastas bort i traingle::intersect (hur glas ska hantera det) om bool insideObj = true, ignorera? 
// @TODO - fixa så att man ser ljuskällan (fixa senare)