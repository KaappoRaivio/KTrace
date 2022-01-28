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

#define DEBUG


int main () {
    constexpr int window_side_length = 1000;
    constexpr int viewport_side_length = 500;

//    Camera camera = {{0, -5, 4}, {0, 0}, 1, {1, 1,}, {viewport_side_length, viewport_side_length}};
    Camera camera = {{0, -5, 8}, {0, 0.5}, 1, {1, 1,}, {viewport_side_length, viewport_side_length}};

    auto triangleTexture = std::make_shared<ImageTexture>("../res/texture3.png");
//    auto triangleTexture = std::make_shared<ImageTexture>("../res/wood.jpg");
    auto planeTexture = std::make_shared<SolidTexture>(Intensity{1, 1, 1});

//
    Material triangleMaterial{planeTexture, 0.5};
    Material sphereMaterial{triangleTexture, 0.5};
    Material planeMaterial{planeTexture};
    Material mirror{std::make_shared<SolidTexture>(SolidTexture{{1, 1, 1}}), 0};

    auto triangle = std::make_shared<Triangle>(
            MyVector3{-5, 6, 3},
            MyVector3{0, 0, 3},
            MyVector3{5, 6, 3},
            &triangleMaterial
    );
    auto plane = std::make_shared<Plane>(MyVector3{0, 0, 1}, 20, &planeMaterial);
    auto sphere1 = std::make_shared<Sphere>(MyVector3{-2.5, 4, 4.5}, 0.3, &sphereMaterial);
    auto sphere2 = std::make_shared<Sphere>(MyVector3{-1, 4, 4.3}, 0.6, &sphereMaterial);
    auto sphere3 = std::make_shared<Sphere>(MyVector3{1, 4, 4}, 1.0, &sphereMaterial);
    auto sphere4 = std::make_shared<Sphere>(MyVector3{0.5, 2, 3}, 0.5, &sphereMaterial);
    auto sphere5 = std::make_shared<Sphere>(MyVector3{-0.75, 2, 3.25}, 0.4, &sphereMaterial);
    auto sphere6 = std::make_shared<Sphere>(MyVector3{-0, 6, 6}, 15, &sphereMaterial);

    Objects sur = {{sphere1.get(), sphere2.get(), sphere3.get(), sphere4.get(), sphere5.get(), triangle.get(), plane.get(),}};
    auto surfaces = std::make_shared<Objects>(sur);

////    Sphere sphere2 = {{-1, 4, 4.3}, 0.6};
////    Sphere sphere3 = {{1, 4, 4}, 1};
////    Sphere sphere4 = {{0.5, 2, 3}, 0.5};
////    Sphere sphere5 = {{-0.75, 2, 3.25}, 0.4};
//    Sphere sphere6 = {{0, 6, 6}, 1.5};
//
//
//

//
//
//
//
    std::vector<Surface*> objects = {

//            sphere1.get(),
//            sphere2.get(),
            surfaces.get(),
//            SingleSceneObject{triangle.get(), triangleMaterial},
//            SingleSceneObject{plane.get(), planeMaterial},
//            SingleSceneObject(sphere1.get(), sphereMaterial),
//            SingleSceneObject(sphere2.get(), sphereMaterial),
//            SingleSceneObject(sphere3.get(), sphereMaterial),
//            SingleSceneObject(sphere4.get(), sphereMaterial),
//            SingleSceneObject(sphere5.get(), sphereMaterial),
////            SingleSceneObject(sphere6, mirror),
    };

    double radius = 0;
    std::vector<LightSource> lights = {
            {{4,     4.5,  4},   Intensity{0.1, 0.1, 1} * 70, radius * 7},
            {{-4,    4.5,  5.5}, Intensity{1, 0.25, 1} * 30,  radius * 3},
            {{-0.12, 3.83, 3.9}, Intensity{1, 1, 0.25} * 1,   radius},
            {{10,    -40,  40},  Intensity{1, 1, 0.8} * 00,   radius * 100},
    };


    auto model = MyOBJLoader::readOBJ("../res/teapot2.obj");
//    auto model = MyOBJLoader::readOBJ("../res/texture.obj");
//    objects.insert(std::end(objects), std::begin(model), std::end(model));
//    std::cout << objects.size() << std::endl;



    Scene scene = {objects, lights, camera, 1, 1};

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
//        camera.setViewplaneDistance(camera.getViewplaneDistance() * 1.01);
//        camera.move({0, 0.1, 0.1});
        camera.move({0, 0, 0});
        window.delay(50000);
    }
#pragma clang diagnostic pop
//    while (true);
    SDL_Quit();

    return 0;
}
