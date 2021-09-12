//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <vector>
#include "Surface.h"
#include "Camera.h"
#include "Color.h"
#include "Triangle.h"

class Scene {
private:
    std::vector<Surface*> objects;
    Camera camera;
public:
    Scene(const std::vector<Surface*>& objects, Camera camera);
    [[nodiscard]] std::vector<std::vector<Color>> trace () const;
    [[nodiscard]] bool do_raycast (const Ray& ray) const;
};



