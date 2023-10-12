#include "../include/Scene.h"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"
#include "../include/Camera.h"

Scene::Scene(int width, int height) : camera(width, height) {
	// Här ska hela scenen skapas men fungerar inte för tillfäller när det skickas vidare till intersect

	// Färger
	ColorRGB white = { 0.4, 0.4, 0.4 };
	ColorRGB red = { 0.4, 0.0, 0.0 };
	ColorRGB green = { 0.0, 0.4, 0.0 };

	Material materialWhite = { white, 0.0f, 0.0f, 0.0f };
	Material materialRed = { red, 0.0f, 0.0f, 0.0f };
	Material materialGreen = { green, 0.0f, 0.0f, 0.0f };

	glm::vec3 p0(0.0f, 6.0f, -5.0f);
	glm::vec3 p1(10.0f, 6.0f, -5.0f);
	glm::vec3 p2(13.0f, 0.0f, -5.0f);
	glm::vec3 p3(10.0f, -6.0f, -5.0f);
	glm::vec3 p4(0.0f, -6.0f, -5.0f);
	glm::vec3 p5(-3.0f, 0.0f, -5.0f);

	glm::vec3 p6(0.0f, 6.0f, 5.0f);
	glm::vec3 p7(10.0f, 6.0f, 5.0f);
	glm::vec3 p8(13.0f, 0.0f, 5.0f);
	glm::vec3 p9(10.0f, -6.0f, 5.0f);
	glm::vec3 p10(0.0f, -6.0f, 5.0f);
	glm::vec3 p11(-3.0f, 0.0f, 5.0f);

	// Glov
	Triangle triangle_floorB{ p0, p4, p5, materialWhite };
	Triangle triangle_floorF{ p1, p3, p2, materialWhite };
	Rectangle rectangle_floor{ p0, p4, p3, p1, materialWhite };

	// Väggar
	Rectangle rectangle_wallH{ p3, p9, p10, p4, materialRed };
	Rectangle rectangle_wallHB{ p4, p10, p11, p5, materialWhite };
	Rectangle rectangle_wallHF{ p2, p3, p9, p8, materialWhite };
	Rectangle rectangle_wallV{ p0, p1, p7, p6, materialGreen };
	Rectangle rectangle_wallVB{ p0, p6, p11, p5, materialWhite };
	Rectangle rectangle_wallVF{ p1, p2, p8, p7, materialWhite };

	// Tak
	Triangle triangle_ceilingB{ p6, p10, p11, materialWhite };
	Triangle triangle_ceilingF{ p7, p8, p9, materialWhite };
	Rectangle rectangle_ceiling{ p6, p7, p9, p10, materialWhite };

	// Lägger till alla polygoner i scenen
	addPolygon(&triangle_floorB);
	addPolygon(&triangle_floorF);
	addPolygon(&rectangle_floor);
	addPolygon(&rectangle_wallH);
	addPolygon(&rectangle_wallHB);
	addPolygon(&rectangle_wallHF);
	addPolygon(&rectangle_wallV);
	addPolygon(&rectangle_wallVB);
	addPolygon(&rectangle_wallVF);
	addPolygon(&triangle_ceilingB);
	addPolygon(&triangle_ceilingF);
	addPolygon(&rectangle_ceiling);
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
