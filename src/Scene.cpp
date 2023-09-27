#include "../include/Scene.h"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"
#include "../include/Camera.h"

Scene::Scene(int width, int height) : camera(width, height) {

	//// Define colors
	//ColorRGB white = { 1.0, 1.0, 1.0 };
	//ColorRGB red = { 1.0, 0.0, 0.0 };
	//ColorRGB green = { 0.0, 1.0, 0.0 };

	//// Floor
	//Triangle triangle_floorB{ glm::vec3{13, 0, -5}, glm::vec3{10, 6, -5}, glm::vec3{10, -6, -5}, white };
	//Triangle triangle_floorF{ glm::vec3{0, 6, -5}, glm::vec3{0, -6, -5}, glm::vec3{-3, 0, -5}, white };
	//Rectangle rectangle_floor{ glm::vec3{10, 6, -5}, glm::vec3{10, -6, -5}, glm::vec3{0, 6, -5}, glm::vec3{0, -6, -5}, white };

	//// Walls
	//Rectangle rectangle_wallH{ glm::vec3{0, 6, 5}, glm::vec3{0, 6, -5}, glm::vec3{10, 6, 5}, glm::vec3{10, 6, -5}, red };
	//Rectangle rectangle_wallHB{ glm::vec3{10, 6, 5}, glm::vec3{10, 6, -5}, glm::vec3{13, 0, 5}, glm::vec3{13, 0, -5}, white };
	//Rectangle rectangle_wallHF{ glm::vec3{0, 6, 5}, glm::vec3{0, 6, -5}, glm::vec3{-3, 0, 5}, glm::vec3{-3, 0, -5}, white };
	//Rectangle rectangle_wallV{ glm::vec3{0, -6, 5}, glm::vec3{-10, -6, 5}, glm::vec3{0, -6, -5}, glm::vec3{0, -6, -5}, green };
	//Rectangle rectangle_wallVB{ glm::vec3{10, -6, 5}, glm::vec3{10, -6, -5}, glm::vec3{13, 0, 5}, glm::vec3{13, 0, -5}, white };
	//Rectangle rectangle_wallVF{ glm::vec3{0, -6, 5}, glm::vec3{0, -6, -5}, glm::vec3{-3, 0, 5}, glm::vec3{-3, 0, -5}, white };

	//// Ceiling
	//Triangle triangle_ceilingB{ glm::vec3{13, 0, 5}, glm::vec3{10, 6, 5}, glm::vec3{10, -6, 5}, white };
	//Triangle triangle_ceilingF{ glm::vec3{0, 6, 5}, glm::vec3{0, -6, 5}, glm::vec3{-3, 0, 5}, white };
	//Rectangle rectangle_ceiling{ glm::vec3{10, 6, 5}, glm::vec3{10, -6, 5}, glm::vec3{0, 6, 5}, glm::vec3{0, -6, 5}, white };

	//// Add objects to the list
	//addPolygon(&triangle_floorB);
	//addPolygon(&triangle_floorF);
	//addPolygon(&rectangle_floor);
	//addPolygon(&rectangle_wallH);
	//addPolygon(&rectangle_wallHB);
	//addPolygon(&rectangle_wallHF);
	//addPolygon(&rectangle_wallV);
	//addPolygon(&rectangle_wallVB);
	//addPolygon(&rectangle_wallVF);
	//addPolygon(&triangle_ceilingB);
	//addPolygon(&triangle_ceilingF);
	//addPolygon(&rectangle_ceiling);
}

void Scene::HemisphericalToLocalCartesian(double phi, double omega, glm::vec3& cartesian) {
	// phi = inclination
	// omega = azimuth
	cartesian.x = cos(phi) * sin(omega);
	cartesian.y = sin(phi) * sin(omega);
	cartesian.z = cos(omega);
}

void Scene::LocalCartesianToWorldCartesian(const glm::vec3& local, const glm::vec3& normal, glm::vec3& world) {
	// Implementera
}

void Scene::LocalCartesianToHemispherical(const glm::vec3& cartesian, double& inclination, double& azimuth) {
	// Implementera
}


void Scene::WorldCartesianToLocalCartesian(const glm::vec3& world, const glm::vec3& normal, glm::vec3& local) {
	// Implementera
}
