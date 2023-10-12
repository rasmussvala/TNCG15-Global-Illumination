#pragma once

#include "ColorRGB.h" // Include necessary headers

struct Material {
    ColorRGB color;        // The color of the material
    float reflectivity;    // Reflectivity of the material (0.0 - 1.0)
    float transparency;    // Transparency of the material (0.0 - 1.0)
    float refractiveIndex; // Refractive index for transparent materials
};
