#pragma once

#include "ColorRGB.h" // Include necessary headers

enum MaterialType {
    Reflective,
    Transparent,
    Diffuse
};

struct Material {
    MaterialType type;          // Type of the material

    union {
        struct {
            ColorRGB color;             // The color of the material
        } diffuseData;

        struct {
            float refractiveIndex;      // Refractive index for transparent materials
        } transparentData;
    };

    Material(MaterialType t) : type(t) {
        if (t == Diffuse) {
            diffuseData.color = ColorRGB(0.0, 0.0, 0.0); // Default color for Diffuse
        }
        else if (t == Transparent) {
            transparentData.refractiveIndex = 1.0f; // Default refractive index for Transparent
        }
    }

    Material(MaterialType t, ColorRGB c) : type(t) {
        if (t == Diffuse) {
            diffuseData.color = c;
        }
        else if (t == Transparent) {
            transparentData.refractiveIndex = 1.0f; // Default refractive index for Transparent
        }
    }

    Material(MaterialType t, float ri) : type(t) {
        if (t == Diffuse) {
            diffuseData.color = ColorRGB(0.0, 0.0, 0.0); // Default color for Diffuse
        }
        else if (t == Transparent) {
            transparentData.refractiveIndex = ri;
        }
    }
};
