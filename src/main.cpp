#pragma once

#include "../include/Cube.h"
#include "../include/Polygon.h"
#include "../include/Scene.h"
#include "../include/Sphere.h"

int main() {
  Scene myScene(300, 300);  // högsta som fungerar på min dator har varit
                            // 400x400 med låga settings

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

  // Parametrar att ändra
  int depthDiffuse = 2;  // bestämmer antalet studsar på diffusa objekt,
                         // rekommendrar 2 och sen ha fler indirekt rays
  int depthReflective =
      5;  // bestämmer antalet studsar på speglar, rekommenderar 5 för då får
          // man spegel i spegel i spegel osv effekt
  int nrOfShadowRays = 10;  // bestämmer antalet shadowrays som ska skjutas till
                            // resp ljuskällor i scenen, mark rekommenderar 100
                            // men jag skulle säga max 10 för vårt
  int nrOfIndirectRays = 1;  // bestämmer antalet rays som ska skapas när det
                             // träffar ett diffust obj
  int samplesPerPixel =
      4;  // bestämmer antalet rays som skjuts ut från en och samma pixel,
          // därefter görs ett medelvärde, krävande!

  myScene.render(depthDiffuse, depthReflective, nrOfShadowRays,
                 nrOfIndirectRays, samplesPerPixel);

  return 0;
}

// @TODO - memoryleaks!
// @TODO - Kolla hur färger blandas - direktljus och indirektljus
// @TODO - fixa rendering till glas
// @TODO - tänk på att ytan vända fel kastas bort i traingle::intersect (hur
// glas ska hantera det) om bool insideObj = true, ignorera?
// @TODO - fixa så att man ser ljuskällan (fixa senare)
