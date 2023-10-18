#pragma once

#include "ColorRGB.h" // Include necessary headers

enum MaterialType {
    REFLECTIVE,
    TRANSPARENT,
    DIFFUSE
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
        if (t == DIFFUSE) {
            diffuseData.color = ColorRGB(0.0, 0.0, 0.0); // Default color for Diffuse
        }
        else if (t == TRANSPARENT) {
            transparentData.refractiveIndex = 1.0f; // Default refractive index for Transparent
        }
    }

    Material(MaterialType t, ColorRGB c) : type(t) {
        if (t == DIFFUSE) {
            diffuseData.color = c;
        }
        else if (t == TRANSPARENT) {
            transparentData.refractiveIndex = 1.0f; // Default refractive index for Transparent
        }
    }

    Material(MaterialType t, float ri) : type(t) {
        if (t == DIFFUSE) {
            diffuseData.color = ColorRGB(0.0, 0.0, 0.0); // Default color for Diffuse
        }
        else if (t == TRANSPARENT) {
            transparentData.refractiveIndex = ri;
        }
    }
};
