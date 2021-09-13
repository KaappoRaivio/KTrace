//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <vector>
#include "Surface.h"
#include "Camera.h"
#include "Color.h"
#include "Triangle.h"
#include "SceneObject.h"

class Scene {
private:
    std::vector<SceneObject> objects;
    Camera camera;
public:
    Scene(std::vector<SceneObject>  objects, Camera camera);
    [[nodiscard]] std::vector<std::vector<Color>> trace () const;
    [[nodiscard]] Color calculate_color (const Ray& ray) const;
};



