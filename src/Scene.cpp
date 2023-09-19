#include "../include/Scene.h"
#include "../include/ColorRGB.h"
#include "../include/Polygon.h"
#include "../include/Camera.h"

void Scene::addScene()
{
    Camera camera{ 600, 600 };

    Triangle triangle_floorB{ glm::vec3{ 13, 0, -5 }, glm::vec3{ 10, 6, -5 }, glm::vec3{ 10, -6, -5 }, {0.0, 1.0 ,0.0} };
    Triangle triangle_floorF{ glm::vec3{ 0, 6, -5 }, glm::vec3{ 0, -6, -5 }, glm::vec3{ -3, 0, -5 }, {0.0, 1.0 ,0.0} };

    Rectangle rectangle_floor{ glm::vec3{ 10, 6, -5 }, glm::vec3{ 10, -6, -5 }, glm::vec3{ 0, 6, -5 }, glm::vec3{ 0, -6, -5 }, {1.0, 0.0 ,0.0}};
    Rectangle rectangle_wallH{ glm::vec3{ 0, 6, 5 }, glm::vec3{ 0, 6, -5 }, glm::vec3{ 10, 6, 5 }, glm::vec3{ 10, 6, -5 }, {0.0, 0.0 ,1.0}};
    Rectangle rectangle_wallL{ glm::vec3{ 0, -6, 5 }, glm::vec3{ 0, -6, -5 }, glm::vec3{ 10, -6, 5 }, glm::vec3{ -10, -6, -5 }, {0.0, 0.0 ,1.0}};
    Rectangle rectangle_wallHB{ glm::vec3{ 10, 6, 5 }, glm::vec3{ 10, 6, -5 }, glm::vec3{ 13, 0, 5 }, glm::vec3{ 13, 0, -5 }, {1.0, 0.0 ,0.0}};
    Rectangle rectangle_wallLB{ glm::vec3{ 10, -6, 5 }, glm::vec3{ 10, -6, -5 }, glm::vec3{ 13, 0, 5 }, glm::vec3{ 13, 0, -5 }, {0.0, 0.5 ,0.5}};

    Rectangle rectangle_ceiling{ glm::vec3{ 10, 6, 5 }, glm::vec3{ 10, -6, 5 }, glm::vec3{ 0, 6, 5 }, glm::vec3{ 0, -6, 5 }, {1.0, 0.0 ,0.0}};
    Triangle triangle_ceilingB{ glm::vec3{ 13, 0, 5 }, glm::vec3{ 10, 6, 5 }, glm::vec3{ 10, -6, 5 }, {0.0, 1.0 ,0.0} };
    Triangle triangle_ceilingF{ glm::vec3{ 0, 6, 5 }, glm::vec3{ 0, -6, 5 }, glm::vec3{ -3, 0, 5 }, {0.0, 1.0 ,0.0} };

    //camera.traceRays({&rectangle_wallHB});
    camera.traceRays({&triangle_floorB, &triangle_floorF, &rectangle_floor, &rectangle_wallH, &rectangle_wallL, 
    &rectangle_wallHB, &rectangle_wallLB, &triangle_ceilingF, &triangle_ceilingB, &rectangle_ceiling});
    camera.saveImage("C:/Users/mahon/Desktop/Globalen/RayTracing-TNGC15/images/test.ppm");

}
