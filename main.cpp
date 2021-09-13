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

#define PRECISION_LIMIT 0.001;

int main () {

    Camera camera = {{0, -5, 7}, {0, 0.25}, 1, {1, 1,}, {4000, 4000}};

//    auto il = {Vector3{-5, 6, 5}, {0,  0, 3}, {5,  6, 3}};
//    std::unique_ptr<Triangle> triangle = std::make_unique<Triangle>(il);
    Triangle t = {Vector3{-5, 6, 5}, {0,  0, 3}, {5,  6, 3}};
    Plane p = {{0, 0, 1}, -2};

    Material m1{Intensity{1, 1, 1}};
    Material m2{Intensity{1, 1, 1}};
//    std::cout << m.albedo << std::endl;


    std::vector<SceneObject> objects = {
            SceneObject{&t, m1},
            SceneObject(&p, m2)
    };
//    std::vector<SceneObject> objects = {SceneObject{&t, m}};
    std::vector<LightSource> lights = {
//            LightSource{{0, 0, 7}, Intensity{1, 0.5, 1} * 25},
//            LightSource{{0, 5, 15}, Intensity{1, 1, 1} * 1},
            LightSource{{-2, 3, 10}, Intensity{1, 1, 0} * 20}
    };

    Scene scene{objects, lights, camera};
//    (std::vector<SceneObject>(), nullptr, Camera(Vector3(), std::pair()));




    std::cout << "starting tracing!" << std::endl;
    auto start = std::chrono::system_clock::now();
    // Some computation here

    auto pixels = scene.trace();

    auto end = std::chrono::system_clock::now();
    std::cout << "traced" << std::endl;

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;




    MyOpenGLWindow window = {4000, 4000, 2, 1};
    window.paint(pixels);
    window.delay(50000);
//    while (true);
    SDL_Quit();

    return 0;
}
