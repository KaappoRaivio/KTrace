#include <iostream>
#include <memory>
#include <chrono>

#include "src/core/interface/MyOpenGLWindow.h"
#include "src/core/light/Intensity.h"
//#include "src/core/common/glm::vec3.h"
#include "src/core/geometry/Plane.h"
#include "src/core/geometry/Triangle.h"
#include "src/core/engine/Camera.h"
#include "src/core/engine/Scene.h"
#include "src/core/engine/SingleSceneObject.h"
#include "src/core/geometry/Sphere.h"
#include "src/core/light/SmoothLightSource.h"
#include "src/core/engine/SolidTexture.h"
#include "src/core/engine/ImageTexture.h"
//#include "src/core/interface/MyOBJLoader.h"
#include "src/core/geometry/Objects.h"
#include "src/core/geometry/BVH.h"
#include "src/core/engine/Scenes.h"
#include "src/core/geometry/CubicBezier.h"
#include <thread>

#define DEBUG


int main () {
    constexpr int window_side_length = 1440;
    constexpr int viewport_side_length = 144;

    Scene scene = Scenes::getScene<3>(viewport_side_length);
//    std::stack<float> a;
//    std::cout << scene.calculateColor({scene.camera.getOrigin(), glm::vec3{0, 0, -1}}, 10, 10, 1, a);
//    std::exit(0);
//    Camera camera = {{-10, -10, 3}, {0, 5, 3}, 1, {1, 1,}, {viewport_side_length, viewport_side_length}};
    CubicBezier b {{-10, -10, 3}, {-2.65, -12.27, 3}, {14.87, -2.65, 3}, {2.07, -1.15, 3}};


    MyOpenGLWindow window = {window_side_length, window_side_length, 2, window_side_length / viewport_side_length, scene.camera};

    float t = 0;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

    double fps = 60;

    while (true) {
        std::cout << "starting tracing!" << std::endl;
        auto start = std::chrono::system_clock::now();
        auto pixels = scene.trace();

        Image rendered = Image{pixels};
        rendered.save("/home/kaappo/git/raytracercpp/out/test.png");


        auto end = std::chrono::system_clock::now();
        std::cout << "traced" << std::endl;

        std::chrono::duration<double> elapsed_seconds = end - start;
        int millis = elapsed_seconds.count();


        window.paint(pixels);
//        std::cout << "moi " << std::endl;
        auto applied = b.apply(t);

        scene.camera.origin = applied.getOrigin();
        scene.camera.direction = applied.getDirection();

//        window.delay(50);

        t += 0.005;
        if (t >= 1) t -= 1;
//        t = t % 1.f;
//        break;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::cout << "finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << " s" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(int((1 / fps - millis) * 1000 )));
    }
#pragma clang diagnostic pop
//    while (true);
    SDL_Quit();

    return 0;
}
