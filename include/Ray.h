#pragma once
#include "../include/ColorRGB.h"
#include "../include/glm/glm.hpp"
#include "../include/Polygon.h"

class Ray {
public:
	glm::vec4 start_vertex;
	glm::vec4 end_vertex; // Optional
	glm::vec4 direction;
	Polygon* surface; // Pointer to the surface
	ColorRGB color;

	Ray(const glm::vec4& start, const glm::vec4& dir, Polygon* surf, const ColorRGB& col)
		: start_vertex(start), direction(dir), surface(surf), color(col) {}
};
