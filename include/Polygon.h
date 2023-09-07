#pragma once

class Polygon {
public:
	// CHATGPT, Denna funktion ska overrideas i Rectangle och Triangle
	// virtual bool intersect(const Ray& ray, glm::dvec4& intersection_point) const = 0;
};

class Rectangle : public Polygon {
public:
	// Implement
};

class Triangle : public Polygon {
public:
	// Implement
};

