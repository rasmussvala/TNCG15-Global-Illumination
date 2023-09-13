#include "../include/glm/glm.hpp"
#include "../include/Camera.h"
#include "../include/ColorRGB.h"
#include <vector>
#include <iostream>
#include <fstream>

int main() {
	Camera camera{ 600, 600 };

	camera.saveImage("../images/test.ppm",
		camera.getWidth(), camera.getHeight(), camera.pixels);
}
