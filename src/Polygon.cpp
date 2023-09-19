#include "../include/Polygon.h"
#include "../include/glm/glm.hpp"

Rectangle::Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, const ColorRGB& col)
	: vertex1(p1), vertex2(p2), vertex3(p3), vertex4(p4), color(col) {
        // Beräkna c1 och c2, som är de två kantvektorerna som utgår från en av hörnen.
        c1 = vertex2 - vertex1;
        c2 = vertex3 - vertex1;

        // Beräkna normalen N till rektangeln som är c1 × c2.
        normal = glm::normalize(glm::cross(c1, c2));
    }


bool Rectangle::intersect(const Ray& ray, glm::vec3& intersectionPoint) const {

    const float EPSILON = 1e-6;

	const glm::vec3& p1 = vertex1;
    const glm::vec3& p2 = vertex2;
    const glm::vec3& p3 = vertex3;
    const glm::vec3& p4 = vertex4;


    float denom = glm::dot(normal, ray.getDirection());
    float t = glm::dot(p1 - ray.getOrigin(), normal) / denom;

    // Om strålen är parallell med rektangelns plan, finns det ingen snittpunkt.
    // Om t är negativt eller nära noll, ligger snittpunkten bakom strålen.
    if ((std::abs(denom) < EPSILON) || (t < 0.0f)) {
        return false;
    }

    // Beräkna snittpunkten.
    glm::vec3 intersection = ray.getOrigin() + t * ray.getDirection();

    // Beräkna a och b.
    float a = glm::dot(intersection - vertex1, c1) / glm::dot(c1, c1);
    float b = glm::dot(intersection - vertex1, c2) / glm::dot(c2, c2);

    // Kontrollera om a och b är inom intervallet [0, 1].
    if (a >= 0.0f && a <= 1.0f && b >= 0.0f && b <= 1.0f) {
        // Snittpunkten är inom rektangeln.
        intersectionPoint = intersection;
        return true;
    }

	return false;
}

Triangle::Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const ColorRGB& col)
	: vertex1(p1), vertex2(p2), vertex3(p3), color(col) {}

bool Triangle::intersect(const Ray& ray, glm::vec3& intersectionPoint) const {
    // M�ller�Trumbore algoritm f�r att hitta snitt mellan ray och triangel

    const float EPSILON = 1e-6;

    glm::vec3 edge1 = vertex2 - vertex1;
    glm::vec3 edge2 = vertex3 - vertex1;
    glm::vec3 h = glm::cross(ray.getDirection(), edge2);
    float a = glm::dot(edge1, h);

    if (a > -EPSILON && a < EPSILON)
        return false; // Ray �r parallell med triangeln

    float f = 1.0f / a;
    glm::vec3 s = ray.getOrigin() - vertex1;
    float u = f * glm::dot(s, h);

    if (u < 0.0 || u > 1.0)
        return false;

    glm::vec3 q = glm::cross(s, edge1);
    float v = f * glm::dot(ray.getDirection(), q);

    if (v < 0.0 || u + v > 1.0)
        return false;

    // Vi har ett snitt, ber�kna t f�r att hitta snittpunkten
    float t = f * glm::dot(edge2, q);

    if (t > EPSILON) {
        intersectionPoint = ray.at(t);
        return true;
    }

    return false; // Snittet �r bakom ray origin (t < 0)
}

