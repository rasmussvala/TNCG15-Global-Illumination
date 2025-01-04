#include "../include/Cube.h"
#include "../include/Polygon.h"
#include "../include/Scene.h"
#include "../include/Sphere.h"
#include "../include/KDTree.h"
#include "../include/Photon.h"

void testKDTree();

int main()
{
  // Test KDTree
  // testKDTree();

  // Set resolution of the rendering
  Scene myScene(600, 600);

  // Sphere params
  float radius = 1.5f;
  Material material{TRANSPARENT, 1.5f};

  // Create a sphere
  glm::vec3 center{7.0f, -2.0f, -1.5f};
  Sphere sphere{center, radius, material};
  myScene.addGeometry(&sphere);

  // Create another sphere
  glm::vec3 center2{6.5f, 2.5f, -1.5f};
  Sphere sphere2{center2, radius, material};
  myScene.addGeometry(&sphere2);

  // Create a rectangular light with a position just below the roof
  Light light{glm::vec3{6.0f, 1.0f, 4.9999f}, glm::vec3{6.0f, -1.0f, 4.9999f},
              glm::vec3{4.0f, -1.0f, 4.9999f}, glm::vec3{4.0f, 1.0f, 4.9999f}};
  myScene.addLight(&light);

  // ----- Parameters to change -----

  // Determines the number of bounces on diffuse objects, recommends 2
  int diffuseBounceCount = 2;

  // Determines the number of bounces on mirrors, recommends 5 for
  // mirror-in-mirror effect
  int mirrorBounceCount = 10;

  // Determines the number of shadow rays to shoot at each light source in the
  // scene. Mark recommends 100, but that's demanding
  int shadowRayCount = 50;

  // Determines the number of rays to create when hitting a diffuse object
  int indirectRayCount = 10;

  // Determines the number of rays shot from a single pixel, then averages them
  // Demanding!
  int raysPerPixel = 4;

  myScene.render(diffuseBounceCount, mirrorBounceCount, shadowRayCount,
                 indirectRayCount, raysPerPixel);

  return 0;
}

void testKDTree()
{
  // Create a KDTree with 3 dimensions
  KDTree tree;

  std::vector<Photon> photons{
      Photon(Ray(glm::vec3(2.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), 1),
      Photon(Ray(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), 1),
      Photon(Ray(glm::vec3(3.0f, 3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), 1),
      Photon(Ray(glm::vec3(4.0f, 4.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), 1),
      Photon(Ray(glm::vec3(5.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), 1),
      Photon(Ray(glm::vec3(6.0f, 6.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), 1),
  };

  // Test insertion
  tree.insert(photons);

  // Print the KDTree structure (optional)
  std::cout << "KDTree structure:" << std::endl;
  tree.print();

  // Test range search
  glm::vec3 searchPoint(2.5f, 4.5f, 0.0f);
  float searchRadius = 2.0f;
  std::vector<Photon> foundPhotons = tree.search(searchPoint, searchRadius);

  // Assertions for range search
  assert(!foundPhotons.empty() && "Search should return some points");

  // Verify that returned points are within the search radius
  for (const auto &photon : foundPhotons)
  {
    float distance = glm::length(photon.ray.getPosition() - searchPoint);
    assert(distance <= searchRadius && "Point should be within search radius");
  }

  std::cout << "KDTree tests passed successfully!" << std::endl;
}