//
// Created by kaappo on 15.2.2022.
//

#include <chrono>
#include <random>
#include "Scenes.h"
#include "Scene.h"
#include "../interface/MyOBJLoader.h"
#include "../geometry/Sphere.h"
#include "../common/mytypes.h"
#include "materials/ImageTexture.h"
#include "materials/Metal.h"

Scene Scenes::getDebug (int windowX, int windowY) {
    Camera camera = {{0, -5.f, 7.f}, {3, 4, 2}, 1.0f, {1.f, (float) windowY / windowX}, {windowX, windowY}};
    Manager<Texture> textureManager;
    Manager<Material> materialManager;

//    Material planeMaterial{polygonTexture};
//    const Texture* planetexture = textureManager.get<SolidTexture>(Intensity{1, 0.5, 0.5});
    const Texture* planetexture = textureManager.get<ImageTexture>("../res/texture3.png");
    auto planeMaterial = materialManager.get<Metal>(planetexture, 0.5);
    std::cout << *planeMaterial << std::endl;
//    auto polygonTexture = textureManager.get<SolidTexture>("../res/texture3.png");
    auto polygonTexture = textureManager.get<SolidTexture>(Intensity{1, 1, 1});
    auto cubeTexture = textureManager.get<SolidTexture>(Intensity{72.2, 45.1, 20} / 100);
    auto polygonsMaterial = materialManager.get<Metal>(polygonTexture, 0.1);
    auto cubeMaterial = materialManager.get<Metal>(cubeTexture, 0.2);

    std::unique_ptr<Surface> plane = std::make_unique<Plane>(glm::vec3{0, 0, 1}, 0, planeMaterial);

    std::vector<std::unique_ptr<Surface>> polygons = MyOBJLoader::readOBJ("../res/teapot2.obj", {4, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, polygonsMaterial);
//    std::vector<std::unique_ptr<Surface>> polygons = MyOBJLoader::readOBJ("../res/texture.obj", {4, 4, 2}, 0.4, {M_PI / 4, -M_PI / 2}, polygonsMaterial);
    std::vector<std::unique_ptr<Surface>> polygons2 = MyOBJLoader::readOBJ("../res/texture.obj", {0, 4, 2}, 0.4, {M_PI / 3.8, -M_PI / 1.4}, cubeMaterial);

    for (auto& p : polygons2) {
        polygons.push_back(std::move(p));
    }

    std::unique_ptr<Surface> bvh = std::make_unique<BVH>(std::move(polygons));

//    Ray ray{{0, -5, 7}, {0.149, 0.872, -0.4652}};
//
//    Intersection i;
//    bvh->getIntersection(ray, i);
//    std::cout << i << std::endl;
//    std::exit(0);



    std::vector<std::unique_ptr<Surface>> objects;
    objects.push_back(std::move(bvh));
    objects.push_back(std::move(plane));


    double radius = 0;
    std::vector<LightSource> lights = {
            {{-2, 1, 100}, Intensity{1, 1, 1} * 2000, radius},
//            {{10, -40, 40},  Intensity{1, 1, 1} * 300, radius * 50},
    };

//    std::exit(0);


    return {std::move(objects), lights, camera, 5, 1, 1, std::move(textureManager), std::move(materialManager)};
}

//Scene Scenes::getSceneOne (int windowX, int windowY) {
//    Camera camera = {{0, -5, 7}, {1, 4, 2}, 0.5, {1, (float) windowY / windowX}, {windowX, windowY}};
//
//
//    Manager textureManager;
//
//    auto triangleTexture = textureManager.getImageTexture("../res/texture3.png");
//    auto earthTexture = textureManager.getImageTexture("../res/earth.png");
//    auto earthBump = textureManager.getImageTexture("../res/earth_bump.jpg");
//
//    auto planeTexture = textureManager.getSolidTexture(Intensity{1, 1, 1});
//
////
//    Material triangleMaterial{planeTexture, 0.5, 1};
//    Material planeMaterial{planeTexture};
//    Material mirror{&SolidTextures::WHITE, 1, 1};
//    Material earthSurface{earthTexture, 0.2, earthBump};
//    Material testSurface{triangleTexture, 0.2, &SolidTextures::BUMP_UP};
//
//    auto triangle = std::make_unique<Triangle>(
//            glm::vec3{-5, 6, 3},
//            glm::vec3{0, 0, 3},
//            glm::vec3{5, 4, 4},
//            triangleMaterial
//    );
//
//    std::unique_ptr<Surface> plane = std::make_unique<Plane>(glm::vec3{0, 0, 1}, 0, planeMaterial);
//    std::unique_ptr<Surface> mirrorSphere = std::make_unique<Sphere>(glm::vec3{1, 6, 5}, 2, mirror);
//    std::unique_ptr<Surface> earth = std::make_unique<Sphere>(glm::vec3{1.5, 1, 1}, 1.5, earthSurface);
//    std::unique_ptr<Surface> test = std::make_unique<Sphere>(glm::vec3{-2, 0.5, 1}, 1.5, testSurface);
//
////    std::vector<std::unique_ptr<Surface>> polygons;
//
//    std::vector<std::unique_ptr<Surface>> polygons = MyOBJLoader::readOBJ("../res/teapot2.obj", {4, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::BLUE_GLOSSY);
//    std::vector<std::unique_ptr<Surface>> polygons2 = MyOBJLoader::readOBJ("../res/uvmaptest.obj", {-2, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::RED_GLOSSY);
////
//    for (auto& pointer : polygons2) {
//        polygons.push_back(std::move(pointer));
//    }
//
//    polygons.push_back(std::move(mirrorSphere));
//    polygons.push_back(std::move(earth));
//    polygons.push_back(std::move(test));
//
//    std::unique_ptr<Surface> bvh = std::make_unique<BVH>(std::move(polygons));
//
//    std::vector<std::unique_ptr<Surface>> objects;
//
//    objects.push_back(std::move(plane));
//    objects.push_back(std::move(bvh));
//
//    double radius = 0;
//    std::vector<LightSource> lights = {
//            {{-2, 1,   3},  Intensity{1, 1, 1} * 21,  radius},
//            {{10, -40, 40}, Intensity{1, 1, 1} * 300, radius * 50},
//    };
//
//    return {std::move(objects), lights, camera, 5, 1, 4, std::move(textureManager)};
//}
//
//Scene Scenes::getSceneTwo (int windowX, int windowY) {
//    Camera camera = {{0, -5, 7}, {1, 4, 2}, 1, {1, (float) windowY / windowX}, {windowX, windowY}};
//
//    Manager textureManager;
//
//    auto triangleTexture = textureManager.getImageTexture("../res/texture3.png");
//    auto earthTexture = textureManager.getImageTexture("../res/earth.png");
//    auto earthBump = textureManager.getImageTexture("../res/test.png");
//
//    auto planeTexture = textureManager.getSolidTexture(Intensity{1, 1, 1});
//
//    Material planeMaterial{planeTexture};
//    Material mirror{&SolidTextures::WHITE, 1, 1};
//    Material earthSurface{earthTexture, 0.4, earthBump};
//    Material testSurface{triangleTexture, 0.2, &SolidTextures::BUMP_UP};
//
//    std::unique_ptr<Surface> plane = std::make_unique<Plane>(glm::vec3{0, 0, 1}, 0, planeMaterial);
//    std::unique_ptr<Surface> mirrorSphere = std::make_unique<Sphere>(glm::vec3{1, 6, 5}, 2, mirror);
//    std::unique_ptr<Surface> earth = std::make_unique<Sphere>(glm::vec3{1.5, 1, 1}, 1.5, earthSurface);
//    std::unique_ptr<Surface> test = std::make_unique<Sphere>(glm::vec3{-2, 0.5, 1}, 1.5, testSurface);
//
//    std::vector<std::unique_ptr<Surface>> polygons = MyOBJLoader::readOBJ("../res/teapot2.obj", {4, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::BLUE_GLOSSY);
//    std::vector<std::unique_ptr<Surface>> polygons2 = MyOBJLoader::readOBJ("../res/uvmaptest.obj", {-2, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::RED_GLOSSY);
////
////    for (auto& pointer : polygons2) {
////        polygons.push_back(std::move(pointer));
////    }
//
//    polygons.push_back(std::move(mirrorSphere));
//    polygons.push_back(std::move(earth));
//    polygons.push_back(std::move(test));
//
//    std::unique_ptr<Surface> bvh = std::make_unique<BVH>(std::move(polygons));
//
//    std::vector<std::unique_ptr<Surface>> objects;
//
//    objects.push_back(std::move(plane));
//    objects.push_back(std::move(bvh));
//
//    double radius = 0;
//    std::vector<LightSource> lights = {
//            {{-2, 1,   3},  Intensity{1, 1, 1} * 21,  radius},
//            {{10, -40, 40}, Intensity{1, 1, 1} * 300, radius * 50},
//    };
//
//    return {std::move(objects), lights, camera, 5, 1, 2, std::move(textureManager)};
//}
//
//Scene Scenes::getSceneThree (int windowX, int windowY) {
//    Camera camera{{-10, -10, 3}, {0, 5, 3}, 1, {1, (float) windowY / windowX,}, {windowX, windowY}};
//
//    Manager textureManager;
//
//    auto planeTexture = textureManager.getImageTexture("../res/texture3.png");
//
//    Material planeMaterial{planeTexture};
//    Material transparent{&SolidTextures::WHITE, 0, 0.2f};
//    transparent.opticalDensity = 1.5;
//
//    Material transparent2{&SolidTextures::WHITE, 0, 0.2f};
//    transparent2.opticalDensity = 1000;
//
//    std::unique_ptr<Surface> plane = std::make_unique<Plane>(glm::vec3{0, -1, 0}, 10, planeMaterial);
//    std::unique_ptr<Surface> plane2 = std::make_unique<Plane>(glm::vec3{0, 0, 1}, 0, Materials::WHITE);
//    std::unique_ptr<Surface> transparentSphere = std::make_unique<Sphere>(glm::vec3{0, 3, 3}, 2, transparent);
//    std::unique_ptr<Surface> transparentSphere2 = std::make_unique<Sphere>(glm::vec3{0, 6, 3}, 1, transparent2);
//    std::unique_ptr<Surface> transparentTriangle = std::make_unique<Triangle>(glm::vec3{-4, 1, 7}, glm::vec3{-4, 1, 3}, glm::vec3{4, 1, 7}, transparent);
//    std::unique_ptr<Surface> transparentTriangle2 = std::make_unique<Triangle>(glm::vec3{-4, 1, 3}, glm::vec3{4, 1, 3}, glm::vec3{4, 1, 7}, transparent);
//
//    std::cout << glm::to_string(plane->getUVAt({0, 1, 0})) << std::endl;
////    std::cout << transparentSphere->refract()
////    std::exit(0);
//
//    std::stack<double> a;
//    a.push(1);
////    auto ray = Ray{{0,    -5,   7},
////                   {0.28, 0.85, -0.43}};
////    const std::optional<Intersection>& intersection = transparentSphere->getIntersection(ray, <#initializer#>);
//
////    std::cout << intersection->distance << std::endl;
////    std::cout << intersection->position << std::endl;
////    std::cout << transparentSphere->refract(intersection.value().position, ray.getDirection(), a) << std::endl;
//
//
////    std::exit(0);
//
//
//    std::vector<std::unique_ptr<Surface>> polygons;
//    polygons.push_back(std::move(transparentSphere));
//    polygons.push_back(std::move(transparentSphere2));
//    auto teapot = MyOBJLoader::readOBJ("../res/uvmaptest.obj", glm::vec3{1.f, 9.f, 3.f}, 0.15, {0, -M_PI / 2}, &Materials::WHITE);
//    for (auto& face : teapot) {
//        polygons.push_back(std::move(face));
//    }
////    polygons.push_back();
////    polygons.push_back(std::move(transparentTriangle));
////    polygons.push_back(std::move(transparentTriangle2));
//    std::unique_ptr<Surface> bvh = std::make_unique<BVH>(std::move(polygons));
//
//    std::vector<std::unique_ptr<Surface>> objects;
//
//    objects.push_back(std::move(plane));
//    objects.push_back(std::move(plane2));
//    objects.push_back(std::move(bvh));
//
//    double radius = 0;
//    std::vector<LightSource> lights = {
//            {{-2, 20,  3},   Intensity{1, 1, 1} * 210,  radius},
//            {{10, -40, 100}, Intensity{1, 1, 1} * 3000, radius * 50},
//    };
//
//
//    return {std::move(objects), lights, camera, 2, 1, 4, std::move(textureManager)};
//}
//
//Scene Scenes::getSceneFour (int windowX, int windowY) {
//
//    Camera camera = {{0, -5, 7}, {0.341747, -5 + 0.808307, 7 - 0.479426}, 1, {1, (float) windowY / windowX}, {windowX, windowY}};
//
//    Manager textureManager;
//
//    auto planeTexture = textureManager.getSolidTexture(Intensity{1, 1, 1});
//
//    Material planeMaterial{planeTexture, 0.0, 1.0};
//
//    std::unique_ptr<Surface> plane = std::make_unique<Plane>(glm::vec3{0, 0, 1}, 0, planeMaterial);
//
//    std::vector<std::unique_ptr<Surface>> polygons = MyOBJLoader::readOBJ("../res/uvmaptest.obj", {4, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::BLUE);
//    std::unique_ptr<Surface> bvh = std::make_unique<BVH>(std::move(polygons));
//
//    std::vector<std::unique_ptr<Surface>> objects;
//    objects.push_back(std::move(plane));
//    objects.push_back(std::move(bvh));
//
//    double radius = 0;
//    std::vector<LightSource> lights = {
//            {{-2,  1,   3},   Intensity{1, 1, 1} * 21,   radius},
//            {{-10, -40, 100}, Intensity{1, 1, 1} * 3000, radius * 25},
//    };
//
//    return {std::move(objects), lights, camera, 3, 1, 1, std::move(textureManager)};
//}
//
//Scene Scenes::getRaytracinginaweekendtestscene (int windowX, int windowY) {
//    Manager manager;
//
//    auto ground = Material{manager.getSolidTexture({1, 0.8, 0.0}), 0, 1.0};
//    auto center = Material{manager.getSolidTexture({0.7, 0.3, 0.3}), 0.8, 1.0};
//    auto left = Material{manager.getSolidTexture({0.8, 0.8, 0.8}), 1, 0.5};
//    left.opticalDensity = 1.5;
//    auto right = Material{manager.getSolidTexture({0.8, 0.6, 0.2}), 0.8, 0.5};
//
//    std::vector<std::unique_ptr<Surface>> o;
////    o.push_back(std::make_unique<Sphere>(glm::vec3{0.0, 0.0, -1.0}, 0.5, center));
//    o.push_back(std::make_unique<Sphere>(glm::vec3{-1.0, 5.0, -1.0}, 0.5, left));
////    o.push_back(std::make_unique<Sphere>(glm::vec3{1.0, 0.0, -1.0}, 0.5, right));
//
//    std::vector<std::unique_ptr<Surface>> objects{};
//    objects.push_back(std::make_unique<BVH>(std::move(o)));
//    objects.push_back(std::make_unique<Plane>(glm::vec3{0, 0, 1}, 1.6, ground));
//
////    std::cout << *objects[1] << std::endl;
//
//    std::vector<LightSource> lights = {
//            {{100, -40, 40}, Intensity{1, 1, 1} * 10000, 0},
//    };
//
//    Camera camera{{0, 0, -1.4}, {-1, 5, -1}, 3, {1, (float) windowY / windowX}, {windowX, windowY}};
//
//    return {std::move(objects), lights, camera, 3, 1, 1, std::move(manager)};
//
//}
//
//Scene Scenes::getBezierScene (int windowX, int windowY, const SplineSequence& sequence) {
//    Manager manager;
//
//
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//
//    std::uniform_real_distribution<float> d(10, 20);
//    std::uniform_real_distribution<float> radiusDistribution(1, 2);
//    std::uniform_real_distribution<float> colorDistribution(0.5, 1);
//    std::uniform_real_distribution<float> glossinessDistribution(0.5, 0.8);
//    std::uniform_real_distribution<float> alphaDistribution(0, 0.5);
//    std::uniform_real_distribution<float> sideDistribution(-1, 1);
//
//
//    std::vector<std::unique_ptr<Surface>> spheres;
//
//    for (float t = 0 ; t < 1 ; t += 0.025f) {
//        const Ray& ray = sequence.apply(t, true);
//        auto forward = ray.getDirection();
//        auto side = glm::normalize(glm::cross(forward, {0.f, 0.f, 1.f}));
//
//        auto& gen = MyRandom::generator;
//        float alpha = alphaDistribution(gen);
//
//        Intensity color{
//                colorDistribution(gen),
//                colorDistribution(gen),
//                colorDistribution(gen)
//        };
//        Material material{manager.getSolidTexture(color), 0.01, 0.1f};
//        material.opticalDensity = 1.2;
//
//
//
//        spheres.push_back(std::make_unique<Sphere>(ray.getOrigin() + 3.f * (sideDistribution(gen) > 0 ? 1 : -1) * side, radiusDistribution(gen), material));
//    }
//
//    std::unique_ptr<Surface> bvh = std::make_unique<BVH>(std::move(spheres));
//
//    std::vector<std::unique_ptr<Surface>> objects;
//    objects.push_back(std::move(bvh));
//
//    std::vector<LightSource> lights = {
//            {{100, -40, 40}, Intensity{1, 1, 1} * 5000, 0},
//    };
//
//    auto planeTexture = manager.getImageTexture("../res/texture3.png");
//    Material planeMaterial{planeTexture};
//    std::unique_ptr<Surface> plane = std::make_unique<Plane>(glm::vec3{0, 0, 1}, 0, planeMaterial);
//    objects.push_back(std::move(plane));
//
//    Camera camera{sequence.apply(0, false).getOrigin(), sequence.apply(0, false).getDirection(), 1, {1.f, (float) windowY / windowX}, {windowX, windowY}};
//    return {std::move(objects), lights, camera, 2, 1, 1, std::move(manager)};
//}