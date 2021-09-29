#include <iostream>
#include <memory>
#include <chrono>

#include "MyOpenGLWindow.h"
#include "Intensity.h"
#include "Vector3.h"
#include "Plane.h"
#include "Triangle.h"
#include "Camera.h"
#include "Scene.h"
#include "SceneObject.h"
#include "Sphere.h"
#include "SmoothLightSource.h"
#include "SolidTexture.h"
#include "ImageTexture.h"


extern const double PRECISION_LIMIT = 0.001;

int main () {
    constexpr int window_side_length = 1000;
    constexpr int viewport_side_length = 200;

    Camera camera = {
            {0, -5, 7},
            {-0.0375, 0.38},
            1,
            {1, 1,},
            {viewport_side_length, viewport_side_length}
    };


    auto triangle = std::make_shared<Triangle>(
            Vector3{-5, 6, 5},
            Vector3{0, 0, 3},
            Vector3{5, 6, 3}
    );
    auto plane = std::make_shared<Plane>(Vector3{0, 0, 1}, -1);
    auto sphere1 = std::make_shared<Sphere>(Vector3{-2.5, 4, 4.5}, 0.3);
    auto sphere2 = std::make_shared<Sphere>(Vector3{-1, 4, 4.3}, 0.6);
    auto sphere3 = std::make_shared<Sphere>(Vector3{1, 4, 4}, 1.0);
    auto sphere4 = std::make_shared<Sphere>(Vector3{0.5, 2, 3}, 0.5);
    auto sphere5 = std::make_shared<Sphere>(Vector3{-0.75, 2, 3.25}, 0.4);
    auto sphere6 = std::make_shared<Sphere>(Vector3{-0, 6, 6}, 15);
//    Sphere sphere2 = {{-1, 4, 4.3}, 0.6};
//    Sphere sphere3 = {{1, 4, 4}, 1};
//    Sphere sphere4 = {{0.5, 2, 3}, 0.5};
//    Sphere sphere5 = {{-0.75, 2, 3.25}, 0.4};
//    Sphere sphere6 = {{0, 6, 6}, 1.5};



//    auto triangleTexture = std::make_shared<ImageTexture>("../res/texture4.png");
    auto triangleTexture = std::make_shared<ImageTexture>("../res/wood.jpg");
    auto planeTexture = std::make_shared<SolidTexture>(Intensity{1, 1, 1});


    Material triangleMaterial{triangleTexture, 0.5};
    Material sphereMaterial{triangleTexture, 0};
    Material planeMaterial{planeTexture};
    Material mirror{std::make_shared<SolidTexture>(SolidTexture{{1, 1, 1}}), 0};





    std::vector<SceneObject> objects = {
            SceneObject{triangle, triangleMaterial},
            SceneObject{plane, planeMaterial},
            SceneObject(sphere1, sphereMaterial),
            SceneObject(sphere2, sphereMaterial),
            SceneObject(sphere3, sphereMaterial),
            SceneObject(sphere4, sphereMaterial),
            SceneObject(sphere5, sphereMaterial),
//            SceneObject(sphere6, mirror),
    };
    double radius = 0.2;
    std::vector<LightSource> lights = {
            {{4,     4.5,  4},   Intensity{0.1, 0.1, 1} * 70, radius},
            {{-4,    4.5,  5.5}, Intensity{1, 0.25, 1} * 30,  radius},
            {{-0.12, 3.83, 3.9}, Intensity{1, 1, 0.25} * 1,   radius},
            {{4,     -40,  40},  Intensity{1, 1, 1} * 800,    radius},
    };


    Scene scene{objects, lights, camera, 4, 8};

    std::cout << "starting tracing!" << std::endl;
    auto start = std::chrono::system_clock::now();

    auto pixels = scene.trace(5);

    auto end = std::chrono::system_clock::now();
    std::cout << "traced" << std::endl;

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;


    MyOpenGLWindow window = {window_side_length, window_side_length, 2, window_side_length / viewport_side_length};
    window.paint(pixels);
//    window.delay(500);
//    while (true);
    SDL_Quit();

    return 0;
}
