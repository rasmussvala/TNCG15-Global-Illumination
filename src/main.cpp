#include "../include/Scene.h"
#include "../include/Polygon.h"
#include "../include/Object.h"

int main() {
	Scene myScene(600, 600);

	// OBS!!! VÄNSTER ÄR HÖGER OCH HÖGER ÄR VÄNSTER NÄR DET RENDERAS

	

	// ----------------------------------------------

	// Default-konstruktor lägger till en liten blå kub
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

	// @TODO - Kolla varför scenen är flippad vertikalt
	// @TODO - Kolla varför scenen inte kan skrivas i konstruktorn
}
