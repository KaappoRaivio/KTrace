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

#define DEBUG


int main () {
    constexpr int window_side_length = 1000;
    constexpr int viewport_side_length = 1000;

    Scene scene = Scenes::getScene<5>(viewport_side_length);
//    std::stack<float> a;
//    std::cout << scene.calculateColor({scene.camera.getOrigin(), glm::vec3{0, 0, -1}}, 10, 10, 1, a);
//    std::exit(0);


    MyOpenGLWindow window = {window_side_length, window_side_length, 2, window_side_length / viewport_side_length, scene.camera};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true) {
        std::cout << "starting tracing!" << std::endl;
        auto start = std::chrono::system_clock::now();
        auto pixels = scene.trace();

        auto end = std::chrono::system_clock::now();
        std::cout << "traced" << std::endl;

        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << " s" << std::endl;


        window.paint(pixels);
        std::cout << "moi " << std::endl;
        scene.camera.origin = scene.camera.origin + glm::vec3(0, 0.1, 0);
        window.delay(50);
        break;
    }
#pragma clang diagnostic pop
//    while (true);
    SDL_Quit();

    return 0;
}
