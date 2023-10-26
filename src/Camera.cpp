#pragma once

#include "../include/Camera.h"


Camera::Camera(int w, int h) : width(w), height(h) {
	MAX_DEPTH = 0; 
	MAX_SHADOWRAYS = 0;
	MAX_INDIRECTRAYS = 0;

	// Allokera minne för pixels
	pixels.resize(height);
	for (int i = 0; i < height; ++i) {
		pixels[i].resize(width);
	}
}

void Camera::saveImage(std::string filename) {
	// CONTRAST STRETCHING
	std::ofstream ppmFile(filename); // Opens/creates the file

	ppmFile << "P3\n" << width << ' ' << height << "\n255\n";

	// Find the maximum pixel value among all channels
	float maxRGB = -1.0f;

	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {
			auto r = pixels[j][i].r;
			auto g = pixels[j][i].g;
			auto b = pixels[j][i].b;

			float maxChannel = (float)std::max({ r, g, b });
			maxRGB = (float)std::max(maxRGB, maxChannel);
		}
	}

	// Calculate the stretching factor
	float stretchFactor = 255.0f / maxRGB;

	// Write the stretched pixel values to the output file
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {
			auto r = pixels[j][i].r;
			auto g = pixels[j][i].g;
			auto b = pixels[j][i].b;

			// Convert to 0-255
			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);
			// Apply contrast stretching using the brightest channel
			ir = static_cast<int>(stretchFactor * r);
			ig = static_cast<int>(stretchFactor * g);
			ib = static_cast<int>(stretchFactor * b);

			ppmFile << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
	ppmFile.close();
}

void Camera::castRays() {

	float progress = 0.0f;

	// Loopar igenom alla pixlar och ansätter färger
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {

			Ray ray(location, rayDirectionFromCamera(i, j));

			// Kollar intersections som sker i scenen  
			pixels[j][i] = castRay(ray, MAX_DEPTH);

			// Visar progress under rendrering
			progressBar(progress / (height * width));
			progress += 1.0f;
		}
	}
}

ColorRGB Camera::castRay(const Ray& ray, int depth) {

	ColorRGB color{};

	if (depth <= 0) {
		return color;
	}

	const float EPSILON = 1e-4f;

	IntersectionResult result = closestIntersect(ray, geometries);

	float t = result.t;
	int index = result.index;

	if (t > EPSILON && t < FLT_MAX) {
		glm::vec3 hitPoint = ray.at(t);

		glm::vec3 hitPointNormal = geometries[index]->getNormal(hitPoint);
		MaterialType materialType = geometries[index]->getMaterial().type;
		
		if (materialType == REFLECTIVE) {
			color = handleReflection(ray, hitPoint, hitPointNormal, depth);
		}
		else { // DIFFUSE
			ColorRGB direct = directLight(hitPoint, hitPointNormal, index);
			ColorRGB indirect = indirectLight(depth, hitPoint, hitPointNormal);
			
			color = direct + (indirect * 0.3f);
		}
	}

	return color;
}

ColorRGB Camera::handleReflection(const Ray& ray, const glm::vec3& hitPoint, const glm::vec3& hitPointNormal, int depth) {
	glm::vec3 reflectDir = glm::reflect(ray.getDirection(), hitPointNormal);
	Ray reflectedRay(hitPoint, reflectDir);

	return castRay(reflectedRay, depth - 1);
	
}

ColorRGB Camera::directLight(const glm::vec3& hitPoint, const glm::vec3& hitPointNormal, int index) {

	ColorRGB colorOfObject = geometries[index]->getMaterial().color;

	float irradiance = 0.0f;

	for (Light* light : lights) {
		irradiance += light->calculateLight(geometries, hitPoint, hitPointNormal, MAX_SHADOWRAYS);
	}

	return colorOfObject * irradiance;
}

ColorRGB Camera::indirectLight(int depth, const glm::vec3& hitPoint, const glm::vec3& hitPointNormal) {
	ColorRGB indirect;

	for (int i = 0; i < MAX_INDIRECTRAYS; i++) {
		Ray randomRay(hitPoint, randomRayDirection(hitPointNormal));
		indirect += castRay(randomRay, depth - 1);
	}

	indirect = indirect / MAX_INDIRECTRAYS;
	return indirect;
}

glm::vec3 Camera::rayDirectionFromCamera(int i, int j) {
	// Beräknar u och v (positionen i world coordinates)
	// u och v är mellan -1 och 1
	float u = 1.0f - (2.0f * i) / width;
	float v = 1.0f - (2.0f * j) / height;

	// Returnerar en normaliserad vektor från kamerans position till u och v
	return glm::normalize(glm::vec3(0.0f, u, v) - location);
}

glm::vec3 Camera::randomRayDirection(const glm::vec3& hitPointNormal) {

	const float PI = 3.14159265359f;

	float yi = static_cast<float>(rand()) / RAND_MAX; // random value [0,1]
	float phi = 2.0f * PI * yi; // azimuth
	float omega = acos(sqrt(1.0f - yi)); // inclination

	glm::vec3 localDir = HemisphericalToLocalCartesian(phi, omega);

	glm::vec3 worldDir = LocalCartesianToWorldCartesian(localDir, hitPointNormal);

	// Make sure the direction is not pointing back into the surface
	if (glm::dot(worldDir, hitPointNormal) < 0.0f) {
		worldDir = -worldDir;
	}

	worldDir = glm::normalize(worldDir);
	return worldDir;
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
		<< " %\r"; // +0.5 for round-off error
	std::cout.flush();
}

glm::vec3 Camera::HemisphericalToLocalCartesian(float phi, float omega) {
	float sinOmega = sin(omega);
	return glm::vec3(
		cos(phi) * sinOmega,
		sin(phi) * sinOmega,
		cos(omega)
	);
}

glm::vec3 Camera::LocalCartesianToWorldCartesian(const glm::vec3& localDir, const glm::vec3& normal) {
	glm::vec3 c = normal;
	glm::vec3 a = glm::normalize(-localDir + glm::dot(normal, localDir) * normal);
	glm::vec3 b = glm::cross(c, a);

	glm::mat3 transformationMatrix(a, b, c);
	glm::vec3 worldDir = transformationMatrix * localDir;

	return worldDir;
}

IntersectionResult closestIntersect(const Ray& ray, const std::vector<Geometry*> geometries) {
	const float EPSILON = 1e-4f;

	float closestT = FLT_MAX;
	int closestIndex = -1; // Initialize to an invalid index

	// Check intersections with polygons
	for (int i = 0; i < geometries.size(); i++) {
		float t = geometries[i]->intersect(ray);
		if (t > EPSILON && t < closestT) {
			closestT = t;
			closestIndex = i;
		}
	}

	return { closestT, closestIndex };
}