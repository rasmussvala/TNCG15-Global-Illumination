#include "../include/Scene.h"
#include "../include/Polygon.h"

int main() {
	Scene myScene(600, 600);

	Triangle triangle1{ glm::vec3{6.0f, 0.0f, 0.0f},
		glm::vec3{7.0f, 0.0f, 2.0f},
		glm::vec3{6.0f, 2.0f, 0.0f},
		ColorRGB(1.0, 1.0, 1.0) };

	myScene.addPolygon(&triangle1);

	Light light1{ glm::vec3{5.0f, 2.0f, 8.0f},
		glm::vec3{5.0f, 2.0f, 10.0f},
		glm::vec3{5.0f, -2.0f, 10.0f},
		glm::vec3{5.0f, -2.0f, 8.0f} };

	myScene.addLight(&light1);

	myScene.render();

	return 0;
}
