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
#include "src/core/engine/materials/SolidTexture.h"
#include "src/core/engine/materials/ImageTexture.h"
//#include "src/core/interface/MyOBJLoader.h"
#include "src/core/geometry/Objects.h"
#include "src/core/geometry/BVH.h"
#include "src/core/engine/Scenes.h"
#include "src/core/geometry/Spline.h"
#include <thread>
#include <ctime>
#include <sstream>
#include <fstream>

#include "src/core/common/mytypes.h"

int main () {
    constexpr int windowWidth = 1440;
    constexpr int windowX = 1440;
    constexpr int windowY = 810;
//    constexpr int windowY = 288;

    SplineSequence sequence = SplineSequence::getRandomSequence(10, {0, 0, 1});


//    Scene scene = Scenes::getBezierScene(windowX, windowY, sequence);
    Scene scene = Scenes::getDebug(windowX, windowY);
//    Scene scene = Scenes::getScene<0>(windowX, windowY);
//    std::stack<float> a;
//    std::cout << scene.calculateColor({scene.camera.getOrigin(), glm::vec3{0, 0, -1}}, 10, 10, 1, a);
//    std::exit(0);
//    Camera camera = {{-10, -10, 3}, {0, 5, 3}, 1, {1, 1,}, {windowX, windowX}};
//    Spline b{{-10, -10, 3}, {-2.65, -12.27, 3}, {23.57,1.87, 3}, {-7.05,3.36, 3}, 0.79};


    MyOpenGLWindow window = {windowWidth, static_cast<int>(static_cast<float>(windowWidth) / windowX * windowY), 2, windowWidth / windowX, scene.camera, scene};

    float t = 0;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"


//    std::this_thread::sleep_for(std::chrono::milliseconds(4000));


    double fps = 60;

//    SplineSequence sequence{{{0, 0, 0},
//                             {1, 0, 0},
//                             {2, 1, 0},
//                             {3, 1, 0}},
//                            1.f};
//


//    SplineSequence sequence{{{0, 0, 2}, {10, 0, 1}, {20, 10, 1}, {25, 0, 1}, {20, -10, 1}}, {{1, 0, 0}, {10, 0, 0}, {5, 0, 0}, {0, -2.5, 0}, {-5, 0, 0}}, 1.f};
//    SplineSequence sequence = SplineSequence::getRandomSequence(5, {0, 0, 0});
//    SplineSequence sequence{{{0, 0, 1}, {5, 0, 1}, {0, 5, 1}, {-2, 10, 1}, {9, -1, 1}}, 1.f};


//    std::exit(0);

//    std::cout << sequence.apply(0) << std::endl;



//    std::ofstream positionCSV;
//    positionCSV.open("../positions.csv");
//    positionCSV << sequence << std::endl;
//    positionCSV << sequence << std::endl;
//    std::exit(0);

//    scene.executeCameraMove(sequence, 0.0005f, [&] (const auto& pixels) {
//    std::exit(0);

    auto start = std::chrono::system_clock::now();
    std::cout << "starting" << std::endl;
//    scene.executeCameraMove(sequence, 0.01f, [&] (const auto& pixels) {
    scene.render([&] (const auto& pixels) {
        Image rendered = Image{pixels};
//        std::cout << scene.camera.origin << ", " << scene.camera.direction << std::endl;
        uint64_t timeSinceEpochMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std::stringstream path;
        path << "/home/kaappo/git/raytracercpp/out/" << timeSinceEpochMilliseconds << ".png";
        rendered.save(path.str());
        window.paint(pixels);
//        positionCSV << scene.camera.origin.x << "," << scene.camera.origin.y
//                                        << "," << scene.camera.origin.z
//                    << '\n';


        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end - start;
        double seconds = elapsed_seconds.count();
//        std::cout << seconds << std::endl;
        std::cout << "sleeping for " << std::chrono::milliseconds(int((1 / fps - seconds) * 1000)).count() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(int((1 / fps - seconds) * 1000)));

        start = std::chrono::system_clock::now();
//        window.delay(50);
    });

//    positionCSV.close();

    system("cd .. && ./plot.sh ./plot.p");
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
