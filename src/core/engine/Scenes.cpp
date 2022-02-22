//
// Created by kaappo on 15.2.2022.
//

#include "Scenes.h"
#include "Scene.h"
#include "../interface/MyOBJLoader.h"
#include "../geometry/Sphere.h"
#include "../common/mytypes.h"

Scene Scenes::getDebug (int viewportSideLength) {
    Camera camera = {{0.0f, -5.0f, 7.0f}, {0, 4, 2}, 1.0f, {1.0f, 1.0f,}, {viewportSideLength, viewportSideLength}};
    TextureManager textureManager;

    auto planeTexture = textureManager.getSolidTexture(Intensity{1, 1, 1});
    Material planeMaterial{planeTexture};

    std::unique_ptr<Surface> plane = std::make_unique<Plane>(glm::vec3{0, 0, 1}, 0, planeMaterial);

//    std::vector<std::unique_ptr<Surface>> polygons = MyOBJLoader::readOBJ("../res/teapot2.obj", {4, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::BLUE_GLOSSY);
    std::vector<std::unique_ptr<Surface>> polygons = MyOBJLoader::readOBJ("../res/texture.obj", {4, 4, 2}, 0.4, {M_PI / 4, -M_PI / 2}, &Materials::BLUE_GLOSSY);
    std::vector<std::unique_ptr<Surface>> polygons2 = MyOBJLoader::readOBJ("../res/texture.obj", {2, 4, 2}, 0.4, {M_PI / 4, -M_PI / 2}, &Materials::RED_GLOSSY);
//    std::vector<std::unique_ptr<Surface>> polygons2 = MyOBJLoader::readOBJ("../res/texture.obj", {4, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::BLUE_GLOSSY);

    for (auto& p : polygons) {
//        polygons.push_back(std::move(p));
        std::cout << *p << std::endl;
    }

    std::unique_ptr<Surface> bvh = std::make_unique<BVH>(std::move(polygons));
    std::cout << *bvh << std::endl;

    std::cout << (std::abs(bvh->getIntersection({{0, -5, 7}, glm::vec3{0.3657, 0.816, -0.5}})->distance) >= PRECISION_LIMIT) << std::endl;


    std::unique_ptr<Surface> obje = std::make_unique<Objects>(std::move(polygons2));
//    std::unique_ptr<Surface> object = std::make_unique<Objects>(std::move(polygones));
    std::vector<std::unique_ptr<Surface>> objects;

//    objects.push_back(std::move(bvh));
    objects.push_back(std::move(plane));
//    std::cout << bvh.get() << std::endl;
//    objects.push_back(std::move(obje));
//    objects.push_back(std::move(plane));

    double radius = 0;
    std::vector<LightSource> lights = {
            {{-2, 1, 3}, Intensity{1, 1, 1} * 21, radius},
//            {{10, -40, 40},  Intensity{1, 1, 1} * 300, radius * 50},
    };

//    std::exit(0);


    return {std::move(objects), lights, camera, 5, 1, 1, std::move(textureManager)};
}

Scene Scenes::getSceneOne (int viewport_side_length) {
    Camera camera = {{0, -5, 7}, {1, 4, 2}, 0.5, {1, 1,}, {viewport_side_length, viewport_side_length}};


    TextureManager textureManager;

    auto triangleTexture = textureManager.getImageTexture("../res/texture3.png");
    auto earthTexture = textureManager.getImageTexture("../res/earth.png");
    auto earthBump = textureManager.getImageTexture("../res/earth_bump.jpg");

    auto planeTexture = textureManager.getSolidTexture(Intensity{1, 1, 1});

//
    Material triangleMaterial{planeTexture, 0.5, 1};
    Material planeMaterial{planeTexture};
    Material mirror{&SolidTextures::WHITE, 1, 1};
    Material earthSurface{earthTexture, 0.2, earthBump};
    Material testSurface{triangleTexture, 0.2, &SolidTextures::BUMP_UP};

    auto triangle = std::make_unique<Triangle>(
            glm::vec3{-5, 6, 3},
            glm::vec3{0, 0, 3},
            glm::vec3{5, 4, 4},
            triangleMaterial
    );

    std::unique_ptr<Surface> plane = std::make_unique<Plane>(glm::vec3{0, 0, 1}, 0, planeMaterial);
    std::unique_ptr<Surface> mirrorSphere = std::make_unique<Sphere>(glm::vec3{1, 6, 5}, 2, mirror);
    std::unique_ptr<Surface> earth = std::make_unique<Sphere>(glm::vec3{1.5, 1, 1}, 1.5, earthSurface);
    std::unique_ptr<Surface> test = std::make_unique<Sphere>(glm::vec3{-2, 0.5, 1}, 1.5, testSurface);

//    std::vector<std::unique_ptr<Surface>> polygons;

    std::vector<std::unique_ptr<Surface>> polygons = MyOBJLoader::readOBJ("../res/teapot2.obj", {4, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::BLUE_GLOSSY);
    std::vector<std::unique_ptr<Surface>> polygons2 = MyOBJLoader::readOBJ("../res/uvmaptest.obj", {-2, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::RED_GLOSSY);
//
    for (auto& pointer : polygons2) {
        polygons.push_back(std::move(pointer));
    }

    polygons.push_back(std::move(mirrorSphere));
    polygons.push_back(std::move(earth));
    polygons.push_back(std::move(test));

    std::unique_ptr<Surface> bvh = std::make_unique<BVH>(std::move(polygons));

    std::vector<std::unique_ptr<Surface>> objects;

    objects.push_back(std::move(plane));
    objects.push_back(std::move(bvh));

    double radius = 0;
    std::vector<LightSource> lights = {
            {{-2, 1,   3},  Intensity{1, 1, 1} * 21,  radius},
            {{10, -40, 40}, Intensity{1, 1, 1} * 300, radius * 50},
    };

    return {std::move(objects), lights, camera, 5, 1, 1, std::move(textureManager)};
}

Scene Scenes::getSceneTwo (int viewport_side_length) {
    Camera camera = {{0, -5, 7}, {1, 4, 2}, 1, {1, 1,}, {viewport_side_length, viewport_side_length}};

    TextureManager textureManager;

    auto triangleTexture = textureManager.getImageTexture("../res/texture3.png");
    auto earthTexture = textureManager.getImageTexture("../res/earth.png");
    auto earthBump = textureManager.getImageTexture("../res/test.png");

    auto planeTexture = textureManager.getSolidTexture(Intensity{1, 1, 1});

    Material planeMaterial{planeTexture};
    Material mirror{&SolidTextures::WHITE, 1, 1};
    Material earthSurface{earthTexture, 0.4, earthBump};
    Material testSurface{triangleTexture, 0.2, &SolidTextures::BUMP_UP};

    std::unique_ptr<Surface> plane = std::make_unique<Plane>(glm::vec3{0, 0, 1}, 0, planeMaterial);
    std::unique_ptr<Surface> mirrorSphere = std::make_unique<Sphere>(glm::vec3{1, 6, 5}, 2, mirror);
    std::unique_ptr<Surface> earth = std::make_unique<Sphere>(glm::vec3{1.5, 1, 1}, 1.5, earthSurface);
    std::unique_ptr<Surface> test = std::make_unique<Sphere>(glm::vec3{-2, 0.5, 1}, 1.5, testSurface);

    std::vector<std::unique_ptr<Surface>> polygons = MyOBJLoader::readOBJ("../res/teapot2.obj", {4, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::BLUE_GLOSSY);
    std::vector<std::unique_ptr<Surface>> polygons2 = MyOBJLoader::readOBJ("../res/uvmaptest.obj", {-2, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::RED_GLOSSY);
//
//    for (auto& pointer : polygons2) {
//        polygons.push_back(std::move(pointer));
//    }

    polygons.push_back(std::move(mirrorSphere));
    polygons.push_back(std::move(earth));
    polygons.push_back(std::move(test));

    std::unique_ptr<Surface> bvh = std::make_unique<BVH>(std::move(polygons));

    std::vector<std::unique_ptr<Surface>> objects;

    objects.push_back(std::move(plane));
    objects.push_back(std::move(bvh));

    double radius = 0;
    std::vector<LightSource> lights = {
            {{-2, 1,   3},  Intensity{1, 1, 1} * 21,  radius},
            {{10, -40, 40}, Intensity{1, 1, 1} * 300, radius * 50},
    };

    return {std::move(objects), lights, camera, 5, 1, 2, std::move(textureManager)};
}

Scene Scenes::getSceneThree (int viewport_side_length) {
    Camera camera = {{0, -10, 3}, {0, 5, 3}, 0.5, {1, 1,}, {viewport_side_length, viewport_side_length}};

    TextureManager textureManager;

    auto planeTexture = textureManager.getImageTexture("../res/texture3.png");

    Material planeMaterial{planeTexture};
    Material transparent{&SolidTextures::WHITE, 0, 0.f};
    transparent.opticalDensity = 2.4;


    std::unique_ptr<Surface> plane = std::make_unique<Plane>(glm::vec3{0, -1, 0}, 10, planeMaterial);
    std::unique_ptr<Surface> plane2 = std::make_unique<Plane>(glm::vec3{0, 0, 1}, 0, Materials::WHITE);
    std::unique_ptr<Surface> transparentSphere = std::make_unique<Sphere>(glm::vec3{0, -1, 3}, 2, transparent);
    std::unique_ptr<Surface> transparentTriangle = std::make_unique<Triangle>(glm::vec3{-4, 1, 7}, glm::vec3{-4, 1, 3},glm::vec3{4, 1, 7},  transparent);
    std::unique_ptr<Surface> transparentTriangle2 = std::make_unique<Triangle>(glm::vec3{-4, 1, 3}, glm::vec3{4, 1, 3},glm::vec3{4, 1, 7},  transparent);

    std::cout << glm::to_string(plane->getUVAt({0, 1, 0})) << std::endl;
//    std::cout << transparentSphere->refract()
//    std::exit(0);

    std::stack<double> a;
    a.push(1);
    auto ray = Ray{{0,    -5,   7},
                   {0.28, 0.85, -0.43}};
    const std::optional<Intersection>& intersection = transparentSphere->getIntersection(ray);

//    std::cout << intersection->distance << std::endl;
//    std::cout << intersection->position << std::endl;
//    std::cout << transparentSphere->refract(intersection.value().position, ray.getDirection(), a) << std::endl;


//    std::exit(0);


    std::vector<std::unique_ptr<Surface>> polygons;
    polygons.push_back(std::move(transparentSphere));
    auto teapot = MyOBJLoader::readOBJ("../res/uvmaptest.obj", glm::vec3{1.f, 9.f, 3.f}, 0.15, {0, -M_PI / 2}, &Materials::WHITE);
    for (auto& face : teapot) {
//        polygons.push_back(std::move(face));
    }
//    polygons.push_back();
//    polygons.push_back(std::move(transparentTriangle));
//    polygons.push_back(std::move(transparentTriangle2));
    std::unique_ptr<Surface> bvh = std::make_unique<BVH>(std::move(polygons));

    std::vector<std::unique_ptr<Surface>> objects;

    objects.push_back(std::move(plane));
    objects.push_back(std::move(plane2));
    objects.push_back(std::move(bvh));

    double radius = 0;
    std::vector<LightSource> lights = {
            {{-2, 20,  3},  Intensity{1, 1, 1} * 210, radius},
            {{10, -40, 100}, Intensity{1, 1, 1} * 3000, radius * 50},
    };


    return {std::move(objects), lights, camera, 4, 1, 1, std::move(textureManager)};
}

Scene Scenes::getSceneFour (int viewport_side_length) {

    Camera camera = {{0, -5, 7}, {0.341747, -5+0.808307, 7-0.479426}, 1, {1, 1,}, {viewport_side_length, viewport_side_length}};

    TextureManager textureManager;

    auto planeTexture = textureManager.getSolidTexture(Intensity{1, 1, 1});

    Material planeMaterial{planeTexture, 0.0, 1.0};

    std::unique_ptr<Surface> plane = std::make_unique<Plane>(glm::vec3{0, 0, 1}, 0, planeMaterial);

    std::vector<std::unique_ptr<Surface>> polygons = MyOBJLoader::readOBJ("../res/uvmaptest.obj", {4, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::BLUE);
    std::unique_ptr<Surface> bvh = std::make_unique<BVH>(std::move(polygons));

    std::vector<std::unique_ptr<Surface>> objects;
    objects.push_back(std::move(plane));
    objects.push_back(std::move(bvh));

    double radius = 1;
    std::vector<LightSource> lights = {
            {{-2, 1,   3},  Intensity{1, 1, 1} * 21,  radius},
            {{10, -40, 40}, Intensity{1, 1, 1} * 300, radius * 50},
    };

    return {std::move(objects), lights, camera, 5, 8, 1, std::move(textureManager)};
}