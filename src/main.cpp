#include "../include/Scene.h"
#include "../include/Polygon.h"

int main() {
	Scene myScene(600, 600);

	Triangle triangle1{ glm::vec3{3.0f, 0.0f, 0.0f},
		glm::vec3{3.0f, 2.0f, 0.0f},
		glm::vec3{3.0f, 0.0f, 2.0f},
		ColorRGB(0.0, 0.0, 0.5) };

	myScene.addPolygon(&triangle1);

	Light light1{ glm::vec3{5.0f, 2.0f, 8.0f},
		glm::vec3{5.0f, 2.0f, 10.0f},
		glm::vec3{5.0f, -2.0f, 10.0f},
		glm::vec3{5.0f, -2.0f, 8.0f} };

	myScene.render();
	return 0;
}
