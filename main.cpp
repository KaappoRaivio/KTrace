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

#include "src/core/common/mytypes.h"

int main () {
    constexpr int windowWidth = 1440;
    constexpr int windowX = 144;
    constexpr int windowY = 81;

    Scene scene = Scenes::getScene<0>(windowX, windowY);
//    std::stack<float> a;
//    std::cout << scene.calculateColor({scene.camera.getOrigin(), glm::vec3{0, 0, -1}}, 10, 10, 1, a);
//    std::exit(0);
//    Camera camera = {{-10, -10, 3}, {0, 5, 3}, 1, {1, 1,}, {windowX, windowX}};
//    CubicBezier b{{-10, -10, 3}, {-2.65, -12.27, 3}, {23.57,1.87, 3}, {-7.05,3.36, 3}, 0.79};


    MyOpenGLWindow window = {windowWidth, static_cast<int>(static_cast<float>(windowWidth) / windowX * windowY), 2, windowWidth / windowX, scene.camera};

    float t = 0;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

    double fps = 60;


//    system("rm /home/kaappo/git/raytracer/out/*.png");
//    CubicBezierSequence sequence{{{-10, 0, 1}, {0, 0, 1}, {10, 0, 1}}, {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}}, 0.9f};
    CubicBezierSequence sequence{{{0, 0, 10}, {10, 0, 5}, {20, 10, 1}, {25, 0, 1}, {20, -10, 1}}, {{1, 0, -2}, {5, 0, -1}, {5, 0, 0}, {0, -5, 0}, {-5, 0, 0}}, 0.9f};
//    std::cout << (sequence.applyDistance(0.5f)) << std::endl;
//    std::exit(0);


    for (float t = 0 ; t < 1 ; t = sequence.advance(t, 0.01f)) {
        std::cout << t << std::endl;
        std::cout << sequence.applyDistance(t) << std::endl;
    }

//    std::exit(0);

//    std::cout << sequence.apply(0) << std::endl;

    auto start = std::chrono::system_clock::now();

    scene.executeCameraMove(sequence, 0.0025f, [&] (const auto& pixels) {
        Image rendered = Image{pixels};
//        std::cout << scene.camera.origin << ", " << scene.camera.direction << std::endl;
        uint64_t timeSinceEpochMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std::stringstream path;
        path << "/home/kaappo/git/raytracercpp/out/" << timeSinceEpochMilliseconds << ".png";
//        rendered.save(path.str());
        window.paint(pixels);


        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end - start;
        double seconds = elapsed_seconds.count();
//        std::cout << seconds << std::endl;
        std::cout << "sleeping for " << std::chrono::milliseconds(int((1 / fps - seconds) * 1000)).count() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(int((1 / fps - seconds) * 1000)));

        start = std::chrono::system_clock::now();
//        window.delay(50);
    });
    window.delay(50);

//    while (true) {
//        std::cout << "starting tracing!" << std::endl;
//        auto pixels = scene.trace();
//
//        Image rendered = Image{pixels};
//        uint64_t timeSinceEpochMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
//        std::stringstream path; path << "/home/kaappo/git/raytracercpp/out/" << timeSinceEpochMilliseconds << ".png";
//        std::cout << rendered.save(path.str()) << std::endl;
//
//
//
//
//        window.paint(pixels);
////        std::cout << "moi " << std::endl;
//        auto applied = b.apply(t);
//
//        scene.camera.origin = applied.getOrigin();
//        scene.camera.direction = applied.getDirection();
//
////        window.delay(50);
//
//        t += 0.0025;
//        if (t >= 1) t -= 1;
//        window.delay(50);
////        t = t % 1.f;
////        break;
//        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//        std::cout << "finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << " s" << std::endl;
//    }
#pragma clang diagnostic pop
//    while (true);
    SDL_Quit();

    return 0;
}
