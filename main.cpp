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

extern const double PRECISION_LIMIT = 0.001;

int main () {

    constexpr int window_side_length = 2000;
    constexpr int viewport_side_length = 2000;

    Camera camera = {{0, -5, 7}, {0, 0.3}, 1, {1, 1,}, {viewport_side_length, viewport_side_length}};

//    auto il = {Vector3{-5, 6, 5}, {0,  0, 3}, {5,  6, 3}};
//    std::unique_ptr<Triangle> triangle = std::make_unique<Triangle>(il);
    Triangle triangle = {Vector3{-5, 6, 5}, {0, 0, 3}, {5, 6, 3}};
    Plane p = {{0, 0, 1}, -1};

    Material triangleTexture{{0.5, 0.5, 0.5}};
    Material m3{Intensity{1, 1, 1}};
//    std::cout << m.albedo << std::endl;


    Material m2{Intensity{1, 1, 1}, 0.7};
    Material m4{Intensity{1, 1, 1}, 1};
    Sphere sphere1 = {{-2.5, 4, 4.5}, 0.3};
    Sphere sphere2 = {{-1, 4, 4.3}, 0.6};
    Sphere sphere3 = {{1, 4, 4}, 1};
    Sphere sphere4 = {{0.5, 2, 3}, 0.5};
    Sphere sphere5 = {{-0.75, 2, 3.25}, 0.4};
    Sphere sphere6 = {{0, 6, 6}, 1.5};

//    std::vector<SceneObject> objects = {SceneObject{&triangle, m}};
    std::vector<SceneObject> objects = {
            SceneObject{&triangle, triangleTexture},
            SceneObject{&p, m3},
            SceneObject(&sphere1, m2),
            SceneObject(&sphere2, m2),
            SceneObject(&sphere3, m2),
            SceneObject(&sphere4, m2),
            SceneObject(&sphere5, m2),
            SceneObject(&sphere6, m4),
    };
    std::vector<LightSource> lights = {
//            LightSource{{-4, 4.5, 5.5}, Intensity{1, 0.25, 1} * 30},
//            LightSource{{-0.12, 3.83, 3.9}, Intensity{1, 1, 0.25} * 1},
            LightSource{{4, -40, 40}, Intensity{1, 1, 1} * 200},

    };

    const auto& a = SmoothLightSource{1, 100,{{4, 4.5, 4}, Intensity{0.1, 0.1, 1} * 70}}.approximate();
    lights.insert(lights.end(), a.begin(), a.end());

    const auto& b = SmoothLightSource(1, 100, LightSource{{-4, 4.5, 5.5}, Intensity{1, 0.25, 1} * 30}).approximate();
    lights.insert(lights.end(), b.begin(), b.end());

    const auto& c = SmoothLightSource(0.5, 100, LightSource{{-0.12, 3.83, 3.9}, Intensity{1, 1, 0.25} * 1}).approximate();
    lights.insert(lights.end(), c.begin(), c.end());


//    std::cout << lights << std::endl;

    Scene scene{objects, lights, camera};
//    (std::vector<SceneObject>(), nullptr, Camera(Vector3(), std::pair()));




    std::cout << "starting tracing!" << std::endl;
    auto start = std::chrono::system_clock::now();
    // Some computation here

    auto pixels = scene.trace(10);

    auto end = std::chrono::system_clock::now();
    std::cout << "traced" << std::endl;

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;




    MyOpenGLWindow window = {window_side_length, window_side_length, 2, window_side_length / viewport_side_length};
    window.paint(pixels);
    window.delay(500);
//    while (true);
    SDL_Quit();

    return 0;
}
