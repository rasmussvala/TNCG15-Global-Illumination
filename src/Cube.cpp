#pragma once

#include "../include/Cube.h"

Material Cube::getMaterial() const { return material; }

std::vector<Geometry *> Cube::getSurfaces()
{
  std::vector<Geometry *> surfaces;
  surfaces.push_back(&surface1);
  surfaces.push_back(&surface2);
  surfaces.push_back(&surface3);
  surfaces.push_back(&surface4);
  surfaces.push_back(&surface5);
  surfaces.push_back(&surface6);
  return surfaces;
}

// Initialize the member variables here
Cube::Cube()
    : color(0.4, 0.4, 0.4),
      material(DIFFUSE, color),
      p0(4.5f, -1.5f, -5.0f),
      p1(7.0f, -1.5f, -5.0f),
      p2(7.0f, -4.0f, -5.0f),
      p3(4.5f, -4.0f, -5.0f),
      p4(4.5f, -1.5f, -2.5f),
      p5(7.0f, -1.5f, -2.5f),
      p6(7.0f, -4.0f, -2.5f),
      p7(4.5f, -4.0f, -2.5f),
      surface1(p0, p1, p2, p3, material), // botten
      surface2(p4, p7, p6, p5, material), // toppen
      surface3(p0, p3, p7, p4, material), // sidan mot kameran
      surface4(p3, p2, p6, p7, material), // sidan mot h�ger
      surface5(p0, p4, p5, p1, material), // sidan mot v�nster
      surface6(p1, p5, p6, p2, material)  // sidan mot bortre v�ggen
{
}
