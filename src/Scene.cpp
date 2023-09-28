#include "../include/Scene.h"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"
#include "../include/Camera.h"

Scene::Scene(int width, int height) : camera(width, height) {
	// Här ska hela scenen skapas men fungerar inte för tillfäller när det skickas vidare till intersect
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
