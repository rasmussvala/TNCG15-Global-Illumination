#include "../include/Camera.h"

#include <chrono> // Include the chrono library for timing

Camera::Camera(size_t w, size_t h) : width(w), height(h)
{
  // Constants will be updated in Scene::render
  MAX_DEPTH_DIFFUSE = 0;
  MAX_DEPTH_REFLECTIVE = 0;
  MAX_SHADOWRAYS = 0;
  MAX_INDIRECTRAYS = 0;

  // Allocate memory for all the pixels in a 1D vector
  pixels.resize(width * height);
}

inline static float linear_to_gamma(float linear_component)
{
  if (linear_component > 0.0f)
    return sqrt(linear_component);

  return 0.0f;
}

void Camera::saveImage(std::string filename)
{
  std::ofstream ppmFile(filename); // Opens/creates the file

  ppmFile << "P3\n"
          << width << ' ' << height << "\n255\n";

  // Write the clamped pixel values to the output file
  for (size_t j = 0; j < height; ++j)
  {
    for (size_t i = 0; i < width; ++i)
    {
      auto &pixel = pixels[j * width + i];
      auto r = pixel.r;
      auto g = pixel.g;
      auto b = pixel.b;

      r = linear_to_gamma(r);
      g = linear_to_gamma(g);
      b = linear_to_gamma(b);

      // Convert to 0-255 and clamp
      int ir = std::min((int)(255 * r), 255);
      int ig = std::min((int)(255 * g), 255);
      int ib = std::min((int)(255 * b), 255);

      ppmFile << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
  ppmFile.close();

  std::cout << "The file has been created at: " + filename + "\n";
}

void Camera::castRays(int raysPerPixel)
{
  // Record the start time
  auto start = std::chrono::high_resolution_clock::now();

  const float updateInterval = 0.05f; // Update progress every 5%
  float nextProgressUpdate = updateInterval;
  size_t totalRows = height;

  Ray ray{};

  // Loop through all pixels and assign colors
  for (size_t j = 0; j < height; ++j)
  {
    for (size_t i = 0; i < width; ++i)
    {
      glm::vec3 colorSum(0.0f);

      // Calculate ray direction once per pixel
      glm::vec3 direction = rayDirectionFromCamera(i, j);

      for (int k = 0; k < raysPerPixel; ++k)
      {
        // Reuse ray object
        ray.setRay(location, direction);

        // Check intersections that occur in the scene
        colorSum += castRay(ray, MAX_DEPTH_DIFFUSE, MAX_DEPTH_REFLECTIVE);
      }

      // Average the color over the number of rays per pixel
      pixels[j * width + i] = colorSum / static_cast<float>(raysPerPixel);
    }

    // Update progress bar less frequently
    float currentProgress = static_cast<float>(j) / totalRows;
    if (currentProgress >= nextProgressUpdate)
    {
      progressBar(currentProgress);
      nextProgressUpdate += updateInterval;
    }
  }

  // Record the end time
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;

  // Print the rendering time
  std::cout << "Rendering completed in " << elapsed.count() << " seconds.\n";
}

void Camera::castPhotons(Scene *scene, int Np)
{
  // Check if we have any transparent spheres
  std::vector<Sphere *> spheres;

  for (const auto &geometry : scene->getGeometries())
  {
    Material material = geometry->getMaterial();
    if (material.type == TRANSPARENT && geometry->getGeometryType() == GeometryType::SPHERE)
    {
      // Add geometry to vector and cast it as a Sphere, not a Geometry to access Sphere functions like getCenter()
      spheres.push_back(dynamic_cast<Sphere *>(geometry));
      std::cout << "one transparent sphere found." << std::endl;
    }
  }

  // Do the photon thingy
  for (const auto &light : scene->getLights())
  {
    for (const auto &sphere : spheres)
    {
      glm::vec3 lightCenter = light->getCenter();
      glm::vec3 sphereCenter = sphere->getCenter();
      glm::vec3 diskNormal = glm::normalize(lightCenter - sphereCenter);

      // Transform the sphere into a plane with a normal pointing towards the light
      std::vector<glm::vec3> sphereDiskBasis = sphere->getDiskBasis(diskNormal);

      for (int i = 0; i < Np; i++)
      {
        glm::vec3 pointOnLight = light->getRandomPoint();
        glm::vec3 pointOnDisk = sphere->getRandomPointOnDisk(sphereDiskBasis[0], sphereDiskBasis[1]);

        // float As = computeProjectedArea(sphereCenter, lightCenter, sphere->getRadius());
      }
    }
  }

  // - random punkter (Xs) från ljuskallan skickas till random punkter (Xe) på disken
  // - lat ljuset studsa till att den nar en diffus yta
  // - spara punkten i kd tree
}

float Camera::computeGeometricFactor(const glm::vec3 &sphereCenter, const glm::vec3 &lightCenter, float sphereRadius)
{
  // Every formula can be found at lec12 page 4

  glm::vec3 distanceVector = lightCenter - sphereCenter;

  // Magnitude of the distance vector (||d||)
  float distanceMagnitude = glm::length(distanceVector);

  // Normalize the distance vector (d / ||d||)
  glm::vec3 unitDistanceVector = glm::normalize(distanceVector);

  // Define the disk normal (Nd) pointing to the light (same as normalized d)
  glm::vec3 diskNormal = unitDistanceVector;

  // Compute the dot product (Nd · (d / ||d||))
  float cosOmegaL = glm::dot(diskNormal, unitDistanceVector);

  // Compute the geometric factor Gm
  return cosOmegaL / (distanceMagnitude * distanceMagnitude);
}

float Camera::computeProjectedArea(const glm::vec3 &sphereCenter, const glm::vec3 &lightCenter, float sphereRadius)
{
  // Compute the geometric factor GM
  float geometricFactor = computeGeometricFactor(sphereCenter, lightCenter, sphereRadius);

  // Compute the projected area As = GM * π * r0^2
  float projectedArea = geometricFactor * PI * sphereRadius * sphereRadius;

  return projectedArea;
}

glm::vec3 Camera::castRay(const Ray &ray, int diffuseBounceCount,
                          int mirrorBounceCount)
{
  glm::vec3 color{0.0f, 0.0f, 0.0f};

  // End of recursion, return black
  if (diffuseBounceCount <= 0 || mirrorBounceCount <= 0)
  {
    return color;
  }

  const std::vector<Geometry *> &geometries = scene->getGeometries();
  hitResult hit = closestIntersect(ray, geometries);

  // We have a hit
  if (hit.t > EPSILON && hit.t < FLT_MAX)
  {
    glm::vec3 hitPoint = ray.at(hit.t);
    Geometry *hitGeometry = geometries[hit.index];

    // REFLECTIVE
    if (hitGeometry->getMaterial().type == REFLECTIVE)
    {
      glm::vec3 reflectDir =
          glm::reflect(ray.getDirection(), hitGeometry->getNormal(hitPoint));
      Ray reflectedRay(hitPoint, reflectDir);

      color = castRay(reflectedRay, diffuseBounceCount, mirrorBounceCount - 1);
    }
    // DIFFUSE
    else if (hitGeometry->getMaterial().type == DIFFUSE)
    {
      glm::vec3 direct =
          directLight(hitPoint, hitGeometry->getNormal(hitPoint), hit.index);
      glm::vec3 indirect =
          indirectLight(diffuseBounceCount, mirrorBounceCount, hitPoint,
                        hitGeometry->getNormal(hitPoint));

      color += direct + (indirect * hitGeometry->getMaterial().color);
    }
    // TRANSPARENT
    else
    {
      // Reflection
      glm::vec3 normal = hitGeometry->getNormal(hitPoint);
      glm::vec3 reflectDir = glm::reflect(ray.getDirection(), normal);
      Ray reflectedRay(hitPoint, reflectDir);
      glm::vec3 reflectColor =
          castRay(reflectedRay, diffuseBounceCount, mirrorBounceCount - 1);

      // Refraction
      float n1 = 1.0f;                                       // Air
      float n2 = hitGeometry->getMaterial().refractiveIndex; // Glass

      glm::vec3 d0 =
          glm::normalize(ray.getDirection()); // Normalize incident direction
      float cosOmega = glm::clamp(glm::dot(d0, normal), -1.0f, 1.0f);

      // We are inside of the glass
      if (cosOmega > 0)
      {
        std::swap(n1, n2);
        normal = -normal; // Invert normal if we are inside the object
      }

      float R = n1 / n2; // Ratio of refractive indices
      float k =
          1 - R * R * (1 - cosOmega * cosOmega); // Snell's law discriminant

      glm::vec3 refractColor(0.0f);
      if (k >= 0)
      { // Total internal reflection check
        glm::vec3 refractDir =
            R * d0 + (R * cosOmega - sqrtf(k)) *
                         normal; // Calculate refraction direction
        Ray refractedRay(hitPoint, refractDir);
        refractColor =
            castRay(refractedRay, diffuseBounceCount, mirrorBounceCount - 1);
      }

      // Fresnel effect (using Schlick's approximation)
      float R0 = powf((n1 - n2) / (n1 + n2), 2);
      float fresnel = R0 + (1 - R0) * powf(1.0f - fabs(cosOmega), 5);

      // Combine reflection and refraction based on Fresnel effect
      color = fresnel * reflectColor + (1 - fresnel) * refractColor;
    }
  }

  return color;
}

glm::vec3 Camera::directLight(const glm::vec3 &hitPoint,
                              const glm::vec3 &hitPointNormal, int index)
{
  const std::vector<Geometry *> &geometries = scene->getGeometries();
  const std::vector<Light *> &lights = scene->getLights();

  glm::vec3 colorOfObject = geometries[index]->getMaterial().color;
  float irradiance = 0.0f;

  for (Light *light : lights)
  {
    irradiance += light->calculateLight(geometries, hitPoint, hitPointNormal,
                                        MAX_SHADOWRAYS);
  }

  return colorOfObject * irradiance;
}

glm::vec3 Camera::indirectLight(int depthDiffuse, int depthReflective,
                                const glm::vec3 &hitPoint,
                                const glm::vec3 &hitPointNormal)
{
  glm::vec3 indirect{0.0f};
  Ray randomRay{};

  for (int i = 0; i < MAX_INDIRECTRAYS; ++i)
  {
    randomRay.setRay(hitPoint, randomRayDirection(hitPointNormal));
    indirect += castRay(randomRay, depthDiffuse - 1, depthReflective);
  }

  indirect /= static_cast<float>(MAX_INDIRECTRAYS);
  return indirect;
}

glm::vec3 Camera::rayDirectionFromCamera(int i, int j) const
{
  // Beräknar u och v (positionen i world coordinates)
  // u och v är mellan -1 och 1
  float u = 1.0f - (2.0f * i) / width;
  float v = 1.0f - (2.0f * j) / height;

  // Returnerar en normaliserad vektor från kamerans position till u och v
  return glm::normalize(glm::vec3(0.0f, u, v) - location);
}

glm::vec3 Camera::randomRayDirection(const glm::vec3 &hitPointNormal)
{
  float random1 = (float)rand() / RAND_MAX; // random value [0,1]
  float random2 = (float)rand() / RAND_MAX; // random value [0,1]
  float phi = 2.0f * PI * random1;          // azimuth [0, 2PI]
  float omega = PI * random2;               // inclination [0, PI]

  glm::vec3 worldDir = sphericalToCartesian(phi, omega);

  // Make sure the direction is not pointing back into the surface
  if (glm::dot(worldDir, hitPointNormal) < 0.0f)
    worldDir = -worldDir;

  return glm::normalize(worldDir);
}

void Camera::progressBar(float percent)
{
  const int BAR_WIDTH = 20;
  const int PROGRESS_THRESHOLD = 2; // Update every 2% change
  static int lastProgress = -PROGRESS_THRESHOLD;

  int currentProgress = static_cast<int>(percent * 100.0f);
  if (currentProgress - lastProgress >= PROGRESS_THRESHOLD)
  {
    lastProgress = currentProgress;

    std::string bar = "[";
    int pos = static_cast<int>(BAR_WIDTH * percent);
    for (int i = 0; i < BAR_WIDTH; ++i)
    {
      if (i <= pos)
        bar += "=";
      else
        bar += " ";
    }
    bar += "] " + std::to_string(currentProgress) + " %\r";

    std::cout << bar;
    std::cout.flush();
  }
}

glm::vec3 Camera::sphericalToCartesian(float phi, float omega)
{
  return glm::vec3(cos(phi) * sin(omega), sin(phi) * sin(omega), cos(omega));
}

void Camera::configure(Scene *newScene,
                       int newDepthDiffuse, int newDepthReflective,
                       int newShadowRays, int newIndirectRays)
{
  scene = newScene;
  MAX_DEPTH_DIFFUSE = newDepthDiffuse;
  MAX_DEPTH_REFLECTIVE = newDepthReflective;
  MAX_SHADOWRAYS = newShadowRays;
  MAX_INDIRECTRAYS = newIndirectRays;
}

hitResult closestIntersect(const Ray &ray,
                           const std::vector<Geometry *> geometries)
{
  const float EPSILON = 1e-4f;

  float closestT = FLT_MAX;
  int closestIndex = -1; // Initialize to an invalid index

  // Check intersections with polygons
  for (size_t i = 0; i < geometries.size(); i++)
  {
    float t = geometries[i]->intersect(ray);
    if (t > EPSILON && t < closestT)
    {
      closestT = t;
      closestIndex = i;
    }
  }

  return {closestT, closestIndex};
}
