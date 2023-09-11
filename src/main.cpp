#include "../include/glm/glm.hpp"
#include "../include/Camera.h"
#include "../include/ColorRGB.h"
#include <vector>
#include <iostream>

int main() {
	Camera camera{ 600, 600 };

	for (int x = 0; x < camera.GetWidth(); x++) {
		for (int y = 0; y < camera.GetHeight(); y++) {
			camera.pixels[x][y] = ColorRGB(1.0, 0.0, 0.0);
		}
	}

	camera.saveImage("C:/Users/Rasmus/Desktop/Skola/MT4B/Advanced Global Illumination and Rendering - TNCG15/RayTracing-TNGC15/images/test.ppm",
		camera.GetWidth(), camera.GetHeight(), camera.pixels);
}
