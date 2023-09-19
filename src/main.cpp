#include "../include/glm/glm.hpp"
#include "../include/Camera.h"
#include "../include/ColorRGB.h"
#include <vector>
#include <iostream>
#include <fstream>

int main() {
	Camera camera{ 600, 600 };

	Triangle triangle1{ glm::vec3{ 3, 0, 0 }, glm::vec3{ 3, 1, 0 }, glm::vec3{ 3, 0, 1 } };

	camera.traceRays({ &triangle1 });

	camera.saveImage("../images/test.ppm");
}
