//
// Created by kaappo on 12.9.2021.
//

#pragma once


#include "Surface.h"
#include "Material.h"
#include "Intersection.h"

class Surface;
class Intersection;

class SceneObject {
private:
    Surface* surface;
    Material material;
public:
    SceneObject(Surface* surface, Material material);


    [[nodiscard]] std::optional<Intersection> get_intersection (const Ray &ray) const;

    [[nodiscard]] const Surface * getSurface() const;
    [[nodiscard]] const Material &getMaterial() const;
};



