#include "../include/glm/glm.hpp"
#include "../include/Camera.h"
#include "../include/ColorRGB.h"
#include <vector>
#include <iostream>
#include <fstream>

int main() {
	Camera camera{ 600, 600 };

	Rectangle rectangle1{ glm::vec3{ 3, 0, 0 }, glm::vec3{ 3, 1, 0 }, glm::vec3{ 3, 1, 0 }, glm::vec3{ 3, 0, 0 } };

	camera.traceRays(camera.pixels, { &rectangle1 });

	camera.saveImage("../images/test.ppm",
		camera.getWidth(), camera.getHeight(), camera.pixels);
}
