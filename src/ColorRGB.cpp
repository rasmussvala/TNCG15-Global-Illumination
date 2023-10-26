#pragma once

#include "../include/ColorRGB.h"

ColorRGB::ColorRGB(double red, double green, double blue)
    : r(red), g(green), b(blue) {}

ColorRGB::ColorRGB() {
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

ColorRGB& ColorRGB::operator+=(const ColorRGB& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

ColorRGB ColorRGB::operator+(const ColorRGB& other) const {
    return ColorRGB(r + other.r, g + other.g, b + other.b);
}

ColorRGB& ColorRGB::operator-=(const ColorRGB& other) {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
}

ColorRGB ColorRGB::operator-(const ColorRGB& other) const {
    return ColorRGB(r - other.r, g - other.g, b - other.b);
}

ColorRGB& ColorRGB::operator*=(const ColorRGB& other) {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
}

ColorRGB ColorRGB::operator*(const ColorRGB& other) const {
    return ColorRGB(r * other.r, g * other.g, b * other.b);
}

ColorRGB& ColorRGB::operator*=(double scalar) {
    r *= scalar;
    g *= scalar;
    b *= scalar;
    return *this;
}

ColorRGB ColorRGB::operator*(double scalar) const {
    return ColorRGB(r * scalar, g * scalar, b * scalar);
}

ColorRGB& ColorRGB::operator/=(double scalar) {
    if (scalar != 0.0) {
        r /= scalar;
        g /= scalar;
        b /= scalar;
    }
    return *this;
}

ColorRGB ColorRGB::operator/(double scalar) const {
    if (scalar != 0.0) {
        return ColorRGB(r / scalar, g / scalar, b / scalar);
    }
    else {
        return ColorRGB();
    }
}

ColorRGB operator*(double scalar, const ColorRGB& color) {
    return ColorRGB(color.r * scalar, color.g * scalar, color.b * scalar);
}