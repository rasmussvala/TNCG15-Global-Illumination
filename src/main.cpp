#pragma once

#include "../include/Cube.h"
#include "../include/Polygon.h"
#include "../include/Scene.h"
#include "../include/Sphere.h"

int main() {
  Scene myScene(300, 300);  // h�gsta som fungerar p� min dator har varit
                            // 400x400 med l�ga settings

  // Default cube adds a blue cube to right hand side
  Cube cube1{};
  myScene.addCube(&cube1);

  // Settings for Sphere
  glm::vec3 center{8.0f, 2.5f, -3.5f};
  float radius = 1.5f;
  // ColorRGB blue{ 0.0f, 0.0f, 0.4f };
  Material materialBlue{REFLECTIVE};

  Sphere sphere1{center, radius, materialBlue};
  myScene.addGeometry(&sphere1);

  Light light1{glm::vec3{5.0f, 1.0f, 4.9999f}, glm::vec3{5.0f, -1.0f, 4.99999f},
               glm::vec3{3.0f, -1.0f, 4.9999f}, glm::vec3{3.0f, 1.0f, 4.9999f}};

  myScene.addLight(&light1);

  // Parametrar att �ndra
  int depthDiffuse = 2;  // best�mmer antalet studsar p� diffusa objekt,
                         // rekommendrar 2 och sen ha fler indirekt rays
  int depthReflective =
      5;  // best�mmer antalet studsar p� speglar, rekommenderar 5 f�r d� f�r
          // man spegel i spegel i spegel osv effekt
  int nrOfShadowRays = 10;  // best�mmer antalet shadowrays som ska skjutas till
                            // resp ljusk�llor i scenen, mark rekommenderar 100
                            // men jag skulle s�ga max 10 f�r v�rt
  int nrOfIndirectRays = 1;  // best�mmer antalet rays som ska skapas n�r det
                             // tr�ffar ett diffust obj
  int samplesPerPixel =
      4;  // best�mmer antalet rays som skjuts ut fr�n en och samma pixel,
          // d�refter g�rs ett medelv�rde, kr�vande!

  myScene.render(depthDiffuse, depthReflective, nrOfShadowRays,
                 nrOfIndirectRays, samplesPerPixel);

  return 0;
}

// @TODO - memoryleaks!
// @TODO - Kolla hur f�rger blandas - direktljus och indirektljus
// @TODO - fixa rendering till glas
// @TODO - t�nk p� att ytan v�nda fel kastas bort i traingle::intersect (hur
// glas ska hantera det) om bool insideObj = true, ignorera?
// @TODO - fixa s� att man ser ljusk�llan (fixa senare)
