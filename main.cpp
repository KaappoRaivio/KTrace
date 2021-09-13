#include <iostream>
#include <memory>

#include "MyOpenGLWindow.h"
#include "Color.h"
#include "Vector3.h"
#include "Plane.h"
#include "Triangle.h"
#include "Camera.h"
#include "Scene.h"
#include "SceneObject.h"

#define PRECISION_LIMIT 0.001;

int main () {

    Camera camera = {{0, -5, 7}, {0, 0.2}, 1, {1, 1,}, {2000, 2000}};

//    auto il = {Vector3{-5, 6, 5}, {0,  0, 3}, {5,  6, 3}};
//    std::unique_ptr<Triangle> triangle = std::make_unique<Triangle>(il);
    Triangle t = {Vector3{-5, 6, 5}, {0,  0, 3}, {5,  6, 3}};
    Material m{Intensity{1, 1, 1}};
    std::cout << m.albedo << std::endl;

    
    std::vector<SceneObject> objects = {SceneObject{t, m}};

    Scene scene{objects, camera};
    auto pixels = scene.trace();

    MyOpenGLWindow window = {2000, 2000, 1.8, 1};
    window.paint(pixels);
    std::cout << "traced" << std::endl;
    window.delay(5000);
//    while (true);
    SDL_Quit();


//    auto viewplane = camera.get_viewplane();
//    for (int row = 0; row < viewplane.size(); ++row) {
//
//        const auto viewplane_row = viewplane[row];
//        for (int column = 0; column < viewplane_row.size(); ++column) {
//            std::cout << viewplane_row[column] << " ";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << camera.get_viewplane() << std::endl;


//    Triangle t = Triangle{{-5, 6, 5}, {0, 0, 3}, {5, 6, 3}};
//    Ray r = {{0, 0, 6}, Vector3{0, 1, -1}.normalize()};

//    std::cout << t.get_intersection_distance(r) << std::endl;

    return 0;
}
