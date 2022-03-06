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
#include <ctime>
#include <sstream>

#define DEBUG


int main () {
    constexpr int window_side_length = 1440;
    constexpr int viewport_side_length = 1440;

    Scene scene = Scenes::getScene<3>(viewport_side_length);
//    std::stack<float> a;
//    std::cout << scene.calculateColor({scene.camera.getOrigin(), glm::vec3{0, 0, -1}}, 10, 10, 1, a);
//    std::exit(0);
//    Camera camera = {{-10, -10, 3}, {0, 5, 3}, 1, {1, 1,}, {viewport_side_length, viewport_side_length}};
    CubicBezier b{{-10, -10, 3}, {-2.65, -12.27, 3}, {23.57,1.87, 3}, {-7.05,3.36, 3}, 0.79};


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
        uint64_t timeSinceEpochMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std::stringstream path; path << "/home/kaappo/git/raytracercpp/out/" << timeSinceEpochMilliseconds << ".png";
        std::cout << rendered.save(path.str()) << std::endl;


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

        t += 0.0025;
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
