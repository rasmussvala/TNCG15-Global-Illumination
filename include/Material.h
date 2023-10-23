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

    // Constructor for MIRROR
    Material(MaterialType t) : type(t), diffuseData({ ColorRGB(0.0, 0.0, 0.0) }) {
        if (t == TRANSPARENT) {
            transparentData.refractiveIndex = 1.0f; // Default refractive index for Transparent
        }
    }

    // Constructor for DIFFUSE
    Material(MaterialType t, ColorRGB c) : type(t), diffuseData({ c }) {
        if (t == TRANSPARENT) {
            transparentData.refractiveIndex = 1.0f; // Default refractive index for Transparent
        }
    }

    // Constructor for TRANSPARENT
    Material(MaterialType t, float ri) : type(t), diffuseData({ ColorRGB(0.0, 0.0, 0.0) }) {
        if (t == TRANSPARENT) {
            transparentData.refractiveIndex = ri;
        }
    }

};
