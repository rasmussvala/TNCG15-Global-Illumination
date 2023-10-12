#include "../include/Scene.h"
#include "../include/Polygon.h"
#include "../include/Object.h"

int main() {
	Scene myScene(600, 600);

	// OBS!!! V�NSTER �R H�GER OCH H�GER �R V�NSTER N�R DET RENDERAS

	

	// ----------------------------------------------

	// Default-konstruktor l�gger till en liten bl� kub
	Cube cube1{};

	myScene.addObjects(&cube1);

	Light light1{ glm::vec3{5.0f, 1.0f, 5.0f},
		glm::vec3{3.0f, 1.0f, 5.0f},
		glm::vec3{3.0f, -1.0f, 5.0f},
		glm::vec3{5.0f, -1.0f, 5.0f}
	};

	myScene.addLight(&light1);

	myScene.render();

	return 0;

	// @TODO - Kolla varf�r scenen �r flippad vertikalt
	// @TODO - Kolla varf�r scenen inte kan skrivas i konstruktorn
}
