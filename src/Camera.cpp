#include "../include/Camera.h"

Camera::Camera(int w, int h) : width(w), height(h), Location(-1, 0, 0, 1) {
	pixels.resize(width, std::vector<ColorRGB>(height, ColorRGB(0.0, 0.0, 0.0)));
}

int Camera::GetWidth() {
	return width;
}

int Camera::GetHeight() {
	return height;
}

glm::vec4 Camera::GetLocation(int x, int y) {
	return glm::vec4(x, y, 0, 1);
}

glm::vec4 Camera::SetLocation(int x, int y, int z) {
	Location = glm::vec4(x, y, z, 1);
	return Location;
}

void Camera::saveImage(std::string filename, int width, int height, const std::vector<std::vector<ColorRGB>>& pixels) {
	std::ofstream ofs;
	ofs.open(filename, std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			ofs.put(static_cast<char>(pixels[x][y].r * 255));
			ofs.put(static_cast<char>(pixels[x][y].g * 255));
			ofs.put(static_cast<char>(pixels[x][y].b * 255));
		}
	}
	ofs.close();
}
