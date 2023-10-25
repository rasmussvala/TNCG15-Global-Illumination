#pragma once

#include "ColorRGB.h" // Include necessary headers

enum MaterialType {
    REFLECTIVE,
    TRANSPARENT,
    DIFFUSE
};

struct Material {
    MaterialType type;       
    ColorRGB color;
    float refractiveIndex;

    // Constructor for MIRROR
    Material(MaterialType t) : type(t), color(ColorRGB(0.0, 0.0, 0.0)), refractiveIndex(1.0f) {}

    // Constructor for DIFFUSE
    Material(MaterialType t, ColorRGB c) : type(t), color(c), refractiveIndex(1.0f) {}

    // Constructor for TRANSPARENT
    Material(MaterialType t, float ri) : type(t), color(ColorRGB(0.0, 0.0, 0.0)), refractiveIndex(ri){}

};
