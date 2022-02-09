#include <iostream>
#include <memory>
#include <chrono>

#include "src/core/interface/MyOpenGLWindow.h"
#include "src/core/light/Intensity.h"
#include "src/core/common/MyVector3.h"
#include "src/core/geometry/Plane.h"
#include "src/core/geometry/Triangle.h"
#include "src/core/engine/Camera.h"
#include "src/core/engine/Scene.h"
#include "src/core/engine/SingleSceneObject.h"
#include "src/core/geometry/Sphere.h"
#include "src/core/light/SmoothLightSource.h"
#include "src/core/engine/SolidTexture.h"
#include "src/core/engine/ImageTexture.h"
#include "src/core/interface/MyOBJLoader.h"
#include "src/core/geometry/Objects.h"
#include "src/core/geometry/BVH.h"

#define DEBUG


int main () {
    constexpr int window_side_length = 1000;
    constexpr int viewport_side_length = 1000;

    Camera camera = {{0, -5, 7}, {0.175, 0.4}, 0.5, {1, 1,}, {viewport_side_length, viewport_side_length}};

    auto triangleTexture = std::make_unique<ImageTexture>("../res/texture3.png");
//    auto triangleTexture = std::make_shared<ImageTexture>("../res/wood.jpg");
    auto earthTexture = std::make_unique<ImageTexture>("../res/earth.png");

    auto planeTexture = std::make_unique<SolidTexture>(Intensity{1, 1, 1});

//
    Material triangleMaterial{planeTexture.get(), 0.5};
    Material sphereMaterial{triangleTexture.get(), 0.5};
    Material planeMaterial{planeTexture.get()};
    Material mirror{&SolidTextures::WHITE, 1};
    Material earthSurface{earthTexture.get(), 0.2};

    auto triangle = std::make_unique<Triangle>(
            MyVector3{-5, 6, 3},
            MyVector3{0, 0, 3},
            MyVector3{5, 4, 4},
            &triangleMaterial
    );

    std::unique_ptr<Surface> plane = std::make_unique<Plane>(MyVector3{0, 0, 1}, 0, &planeMaterial);
    std::unique_ptr<Surface> sphere1 = std::make_unique<Sphere>(MyVector3{-2.5, 4, 4.5}, 0.3, &sphereMaterial);
    std::unique_ptr<Surface> sphere2 = std::make_unique<Sphere>(MyVector3{-1, 4, 4.3}, 0.6, &sphereMaterial);
    std::unique_ptr<Surface> sphere3 = std::make_unique<Sphere>(MyVector3{1, 4, 4}, 1.0, &sphereMaterial);
    std::unique_ptr<Surface> sphere4 = std::make_unique<Sphere>(MyVector3{0.5, 2, 3}, 0.5, &sphereMaterial);
    std::unique_ptr<Surface> sphere5 = std::make_unique<Sphere>(MyVector3{-0.75, 2, 3.25}, 0.4, &sphereMaterial);
    std::unique_ptr<Surface> sphere6 = std::make_unique<Sphere>(MyVector3{-0, 6, 6}, 15, &sphereMaterial);
    std::unique_ptr<Surface> mirrorSphere = std::make_unique<Sphere>(MyVector3{1, 6, 5}, 2, &mirror);
    std::unique_ptr<Surface> earth = std::make_unique<Sphere>(MyVector3{1.5, 1, 1}, 1.5, &earthSurface);

    std::cout << sphereMaterial.get_albedo_at({0.5, 0.7, 1}) << std::endl;

    std::vector<std::unique_ptr<Surface>> polygons = MyOBJLoader::readOBJ("../res/uvmaptest.obj", {4, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::BLUE_GLOSSY);
//    std::vector<std::unique_ptr<Surface>> polygons = MyOBJLoader::readOBJ("../res/texture.obj", {0, 0, 0}, 2, {0, 0}, &sphereMaterial);
    std::vector<std::unique_ptr<Surface>> polygons2 = MyOBJLoader::readOBJ("../res/uvmaptest.obj", {-2, 4, 2}, 0.25, {M_PI / 4, -M_PI / 2}, &Materials::RED_GLOSSY);
//    std::vector<std::unique_ptr<Surface>> polygons3 = MyOBJLoader::readOBJ("../res/teapot.obj", {-2, 20, 0}, 1, {M_PI / 4, -M_PI / 2}, &Materials::GREEN_GLOSSY);

    for (auto& pointer : polygons2) {
        polygons.push_back(std::move(pointer));
    }

    polygons.push_back(std::move(mirrorSphere));
    polygons.push_back(std::move(earth));

    std::unique_ptr<Surface> model = std::make_unique<BVH>(polygons);
    std::cout << model->getBoundingBox() << std::endl;

    std::vector<Surface*> objects = {
            plane.get(),
            model.get(),
    };

    double radius = 0.5;
    std::vector<LightSource> lights = {
            {{-2, 1, 3}, Intensity{1, 1, 1} * 21, radius},
//            {{4, 4.5, 10}, Intensity{1, 1, 1} * 30,  radius * 3},
            {{10, -40, 40},  Intensity{1, 1, 1} * 300, radius * 50},
    };

    Scene scene = {objects, lights, camera, 32, 2};
    MyOpenGLWindow window = {window_side_length, window_side_length, 2, window_side_length / viewport_side_length};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true) {
        std::cout << "starting tracing!" << std::endl;
        auto start = std::chrono::system_clock::now();
        auto pixels = scene.trace(5);

        auto end = std::chrono::system_clock::now();
        std::cout << "traced" << std::endl;

        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << " s" << std::endl;


        window.paint(pixels);
        std::cout << "moi " << std::endl;
        window.delay(50);
        break;
    }
#pragma clang diagnostic pop
//    while (true);
    SDL_Quit();

    return 0;
}
