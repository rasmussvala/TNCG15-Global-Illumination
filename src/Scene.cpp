#include "../include/Scene.h"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"
#include "../include/Camera.h"

Scene::Scene(int width, int height) : camera(width, height) {
	Triangle triangle_floorB{ glm::vec3{ 13, 0, -5 }, glm::vec3{ 10, 6, -5 }, glm::vec3{ 10, -6, -5 }, {0.0, 1.0 ,0.0} };
	objects.push_back(&triangle_floorB);
	Triangle triangle_floorF{ glm::vec3{ 0, 6, -5 }, glm::vec3{ 0, -6, -5 }, glm::vec3{ -3, 0, -5 }, {0.0, 1.0 ,0.0} };
	objects.push_back(&triangle_floorF);

	Rectangle rectangle_floor{ glm::vec3{ 10, 6, -5 }, glm::vec3{ 10, -6, -5 }, glm::vec3{ 0, 6, -5 }, glm::vec3{ 0, -6, -5 }, {1.0, 0.0 ,0.0} };
	objects.push_back(&rectangle_floor);
	Rectangle rectangle_wallH{ glm::vec3{ 0, 6, 5 }, glm::vec3{ 0, 6, -5 }, glm::vec3{ 10, 6, 5 }, glm::vec3{ 10, 6, -5 }, {0.0, 0.0 ,1.0} };
	objects.push_back(&rectangle_wallH);
	Rectangle rectangle_wallL{ glm::vec3{ 0, -6, 5 }, glm::vec3{ 0, -6, -5 }, glm::vec3{ 10, -6, 5 }, glm::vec3{ -10, -6, -5 }, {0.0, 0.0 ,1.0} };
	objects.push_back(&rectangle_wallL);
	Rectangle rectangle_wallHB{ glm::vec3{ 10, 6, 5 }, glm::vec3{ 10, 6, -5 }, glm::vec3{ 13, 0, 5 }, glm::vec3{ 13, 0, -5 }, {1.0, 0.0 ,0.0} };
	objects.push_back(&rectangle_wallHB);
	Rectangle rectangle_wallLB{ glm::vec3{ 10, -6, 5 }, glm::vec3{ 10, -6, -5 }, glm::vec3{ 13, 0, 5 }, glm::vec3{ 13, 0, -5 }, {0.0, 0.5 ,0.5} };
	objects.push_back(&rectangle_wallLB);

	Rectangle rectangle_ceiling{ glm::vec3{ 10, 6, 5 }, glm::vec3{ 10, -6, 5 }, glm::vec3{ 0, 6, 5 }, glm::vec3{ 0, -6, 5 }, {1.0, 0.0 ,0.0} };
	objects.push_back(&rectangle_ceiling);
	Triangle triangle_ceilingB{ glm::vec3{ 13, 0, 5 }, glm::vec3{ 10, 6, 5 }, glm::vec3{ 10, -6, 5 }, {0.0, 1.0 ,0.0} };
	objects.push_back(&triangle_ceilingB);
	Triangle triangle_ceilingF{ glm::vec3{ 0, 6, 5 }, glm::vec3{ 0, -6, 5 }, glm::vec3{ -3, 0, 5 }, {0.0, 1.0 ,0.0} };
	objects.push_back(&triangle_ceilingF);
}