#pragma once

#include "../include/Camera.h"

Camera::Camera(int w, int h) : width(w), height(h) {
  MAX_DEPTH_DIFFUSE = 0;
  MAX_DEPTH_REFLECTIVE = 0;
  MAX_SHADOWRAYS = 0;
  MAX_INDIRECTRAYS = 0;

  // Allokera minne för pixels
  pixels.resize(height);
  for (int i = 0; i < height; ++i) {
    pixels[i].resize(width);
  }
}

void Camera::saveImage(std::string filename) {
  std::ofstream ppmFile(filename);  // Opens/creates the file

  ppmFile << "P3\n" << width << ' ' << height << "\n255\n";

  // Write the clamped pixel values to the output file
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      auto r = pixels[j][i].r;
      auto g = pixels[j][i].g;
      auto b = pixels[j][i].b;

      // Convert to 0-255 and clamp
      int ir = std::min(static_cast<int>(255.999 * r), 255);
      int ig = std::min(static_cast<int>(255.999 * g), 255);
      int ib = std::min(static_cast<int>(255.999 * b), 255);

      ppmFile << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
  ppmFile.close();

  std::cout << "The file has been created at: " + filename + "\n";
}

void Camera::castRays(int samplesPerPixel) {
  float progress = 0.0f;
  Ray ray{};

  // Loopar igenom alla pixlar och ansätter färger
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      for (int k = 0; k < samplesPerPixel; k++) {
        // Skapar en ray från kamerans position till pixlens position
        ray.setRay(location, rayDirectionFromCamera(i, j));

        // Kollar intersections som sker i scenen
        pixels[j][i] += castRay(ray, MAX_DEPTH_DIFFUSE, MAX_DEPTH_REFLECTIVE);
      }

      // Delar på antalet samplesPerPixel
      pixels[j][i] = pixels[j][i] / (float)samplesPerPixel;

      // Visar progress under rendrering
      progressBar(progress / (height * width));
      progress += 1.0f;
    }
  }
}

glm::vec3 Camera::castRay(const Ray& ray, int depthDiffuse,
                          int depthReflective) {
  glm::vec3 color{0.0f, 0.0f, 0.0f};

  if (depthDiffuse <= 0 || depthReflective <= 0) {
    return color;
  }

  hitResult hit = closestIntersect(ray, geometries);

  if (hit.t > EPSILON && hit.t < FLT_MAX) {
    glm::vec3 hitPoint = ray.at(hit.t);

    if (geometries[hit.index]->getMaterial().type == REFLECTIVE) {
      glm::vec3 reflectDir = glm::reflect(
          ray.getDirection(), geometries[hit.index]->getNormal(hitPoint));
      Ray reflectedRay(hitPoint, reflectDir);

      color = castRay(reflectedRay, depthDiffuse, depthReflective - 1);
    } else {  // DIFFUSE
      glm::vec3 direct = directLight(
          hitPoint, geometries[hit.index]->getNormal(hitPoint), hit.index);
      glm::vec3 indirect =
          indirectLight(depthDiffuse, depthReflective, hitPoint,
                        geometries[hit.index]->getNormal(hitPoint));

      color += direct + (indirect * geometries[hit.index]->getMaterial().color);
    }
  }

  return color;
}

glm::vec3 Camera::directLight(const glm::vec3& hitPoint,
                              const glm::vec3& hitPointNormal, int index) {
  glm::vec3 colorOfObject = geometries[index]->getMaterial().color;

  float irradiance = 0.0f;

  for (Light* light : lights) {
    irradiance += light->calculateLight(geometries, hitPoint, hitPointNormal,
                                        MAX_SHADOWRAYS);
  }

  return colorOfObject * irradiance;
}

glm::vec3 Camera::indirectLight(int depthDiffuse, int depthReflective,
                                const glm::vec3& hitPoint,
                                const glm::vec3& hitPointNormal) {
  glm::vec3 indirect{};
  Ray randomRay{};

  for (int i = 0; i < MAX_INDIRECTRAYS; i++) {
    randomRay.setRay(hitPoint, randomRayDirection(hitPointNormal));
    indirect += castRay(randomRay, depthDiffuse - 1, depthReflective);
  }

  indirect = indirect / (float)MAX_INDIRECTRAYS;
  return indirect;
}

glm::vec3 Camera::rayDirectionFromCamera(int i, int j) const {
  // Beräknar u och v (positionen i world coordinates)
  // u och v är mellan -1 och 1
  float u = 1.0f - (2.0f * i) / width;
  float v = 1.0f - (2.0f * j) / height;

  // Returnerar en normaliserad vektor från kamerans position till u och v
  return glm::normalize(glm::vec3(0.0f, u, v) - location);
}

glm::vec3 Camera::randomRayDirection(const glm::vec3& hitPointNormal) {
  float yi = static_cast<float>(rand()) / RAND_MAX;  // random value [0,1]
  float phi = 2.0f * PI * yi;                        // azimuth [0, 2PI]
  float omega = acos(sqrt(1.0f - yi));               // inclination [0, PI/2]

  /*float phi = static_cast<float>(rand()) / RAND_MAX * 2.0f * PI;
  float omega = static_cast<float>(rand()) / RAND_MAX * PI / 2.0f;*/

  glm::vec3 localDir = HemisphericalToLocalCartesian(phi, omega);
  glm::vec3 worldDir = LocalCartesianToWorldCartesian(localDir, hitPointNormal);

  // Make sure the direction is not pointing back into the surface
  if (glm::dot(worldDir, hitPointNormal) < 0.0f) {
    worldDir = -worldDir;
  }

  return glm::normalize(worldDir);
}

void Camera::progressBar(float percent) {
  const int BAR_WIDTH = 20;

  std::cout << "[";
  int pos = (int)(BAR_WIDTH * percent);
  for (int i = 0; i < BAR_WIDTH; ++i) {
    if (i <= pos)
      std::cout << "=";
    else
      std::cout << " ";
  }
  std::cout << "] " << int(percent * 100.0f + 0.5f)
            << " %\r";  // +0.5 for round-off error
  std::cout.flush();
}

glm::vec3 Camera::HemisphericalToLocalCartesian(float phi, float omega) {
  float sinOmega = sin(omega);
  return glm::vec3(cos(phi) * sinOmega, sin(phi) * sinOmega, cos(omega));
}

glm::vec3 Camera::LocalCartesianToWorldCartesian(const glm::vec3& localDir,
                                                 const glm::vec3& normal) {
  glm::vec3 c = normal;
  glm::vec3 a = glm::normalize(-localDir + glm::dot(normal, localDir) * normal);
  glm::vec3 b = glm::cross(c, a);

  glm::mat3 transformationMatrix(a, b, c);

  return transformationMatrix * localDir;
}

hitResult closestIntersect(const Ray& ray,
                           const std::vector<Geometry*> geometries) {
  const float EPSILON = 1e-4f;

  float closestT = FLT_MAX;
  int closestIndex = -1;  // Initialize to an invalid index

  // Check intersections with polygons
  for (int i = 0; i < geometries.size(); i++) {
    float t = geometries[i]->intersect(ray);
    if (t > EPSILON && t < closestT) {
      closestT = t;
      closestIndex = i;
    }
  }

  return {closestT, closestIndex};
}
