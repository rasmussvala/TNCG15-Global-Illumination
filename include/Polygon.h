#pragma once
#include "../include/glm/glm.hpp"
#include "../include/Ray.h"

class Polygon {
public:
	// This function is overridden by the derived classes intersect function 
    virtual bool intersect(const Ray& ray, glm::vec4& intersection_point) const = 0;
};

class Rectangle : public Polygon {
public:
    glm::vec4 p1, p2, p3, p4; // Vertices of the rectangle

    Rectangle(const glm::vec4& vertex1, const glm::vec4& vertex2,
        const glm::vec4& vertex3, const glm::vec4& vertex4)
        : p1(vertex1), p2(vertex2), p3(vertex3), p4(vertex4) {}

    // Override the intersect method from the Polygon base class
    bool intersect(const Ray& ray, glm::vec4& intersection_point) const override {
        // Implementation
        return true;
    }
};



class Triangle : public Polygon {
public:
	// Implement
};

