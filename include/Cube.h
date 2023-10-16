#pragma once
#include "../include/glm/glm.hpp"
#include "../include/Ray.h"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"
#include "../include/Material.h"
#include <vector>

class Cube {
public:
	glm::vec3 getNormal(const glm::vec3& point) const { return { 0,0,0 }; }
	Material getMaterial() const { return material; }
	std::vector<Polygon*> getSurfaces() {
		std::vector<Polygon*> surfaces;
		surfaces.push_back(&surface1);
		surfaces.push_back(&surface2);
		surfaces.push_back(&surface3);
		surfaces.push_back(&surface4);
		surfaces.push_back(&surface5);
		surfaces.push_back(&surface6);
		return surfaces;
	}
private:
	ColorRGB color{ 0.0,0.0,0.4 }; // blue, DENNA SKA INTE FINNAS HÄR SENARE 

	Material material{ color, 0.5, 0.0, 0.0 };

	glm::vec3 p0{ 5.0f, 3.0f, 0.0f };
	glm::vec3 p1{ 6.0f, 3.0f, 0.0f };
	glm::vec3 p2{ 6.0f, 4.0f, 0.0f };
	glm::vec3 p3{ 5.0f, 4.0f, 0.0f };
	glm::vec3 p4{ 5.0f, 3.0f, 1.0f };
	glm::vec3 p5{ 6.0f, 3.0f, 1.0f };
	glm::vec3 p6{ 6.0f, 4.0f, 1.0f };
	glm::vec3 p7{ 5.0f, 4.0f, 1.0f };

	Rectangle surface1{ p0, p1, p2, p3, material }; // botten
	Rectangle surface2{ p4, p7, p6, p5, material }; // toppen
	Rectangle surface3{ p0, p3, p7, p4, material }; // sidan mot kameran
	Rectangle surface4{ p3, p2, p6, p7, material }; // sidan mot höger
	Rectangle surface5{ p0, p4, p5, p1, material }; // sidan mot vänster
	Rectangle surface6{ p1, p5, p6, p2, material }; // sidan mot bortre väggen
};