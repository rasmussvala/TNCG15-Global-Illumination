#pragma once

#include "../include/Scene.h"
#include "../include/Polygon.h"
#include "../include/Cube.h"
#include "../include/Sphere.h"

int main() {
	Scene myScene(200, 200);

	// OBS!!! VÄNSTER ÄR HÖGER OCH HÖGER ÄR VÄNSTER NÄR DET RENDERAS

	// Färger
	ColorRGB white = { 0.4, 0.4, 0.4 };
	ColorRGB red = { 0.4, 0.0, 0.0 };
	ColorRGB green = { 0.0, 0.4, 0.0 };

	Material materialWhite(Diffuse, white); // White diffuse material
	Material materialRed(Diffuse, red); // Red diffuse material
	Material materialGreen(Diffuse, green); // Green diffuse material
	Material mirror(Reflective); // mirror
	Material glas(Transparent, 1.5); // glas with refractiveIndex 1.5
	Material test(Reflective);

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
	Rectangle rectangle_wallHF{ p2, p3, p9, p8, mirror };
	Rectangle rectangle_wallV{ p0, p1, p7, p6, materialGreen };
	Rectangle rectangle_wallVB{ p0, p6, p11, p5, materialWhite };
	Rectangle rectangle_wallVF{ p1, p2, p8, p7, materialWhite };

	// Tak
	Triangle triangle_ceilingB{ p6, p10, p11, materialWhite };
	Triangle triangle_ceilingF{ p7, p8, p9, materialWhite };
	Rectangle rectangle_ceiling{ p6, p7, p9, p10, materialWhite };

	// Lägger till alla polygoner i scenen
	myScene.addPolygon(&triangle_floorB);
	myScene.addPolygon(&triangle_floorF);
	myScene.addPolygon(&rectangle_floor);
	myScene.addPolygon(&rectangle_wallH);
	myScene.addPolygon(&rectangle_wallHB);
	myScene.addPolygon(&rectangle_wallHF);
	myScene.addPolygon(&rectangle_wallV);
	myScene.addPolygon(&rectangle_wallVB);
	myScene.addPolygon(&rectangle_wallVF);
	myScene.addPolygon(&triangle_ceilingB);
	myScene.addPolygon(&triangle_ceilingF);
	myScene.addPolygon(&rectangle_ceiling);

	// ----------------------------------------------

	// Default-konstruktor lägger till en liten blå kub och en sfär i (5,0,0); 
	Cube cube1{};
	myScene.addCube(&cube1);

	/*Sphere sphere1{};
	myScene.addSphere(&sphere1);*/

	Light light1{ glm::vec3{5.0f, 1.0f, 4.9999f},
		glm::vec3{3.0f, 1.0f, 4.9999f},
		glm::vec3{3.0f, -1.0f, 4.9999f},
		glm::vec3{5.0f, -1.0f, 4.9999f}
	};

	myScene.addLight(&light1);

	myScene.render();

	return 0;

	// @TODO - Kolla varför scenen är flippad vertikalt
	// @TODO - Kolla varför scenen inte kan skrivas i konstruktorn
	// @TODO - Polygons kan ibland få snitt i sig själv när shadow rays castas 
}
