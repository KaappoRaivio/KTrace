//
// Created by kaappo on 12.9.2021.
//

#pragma once

#include <memory>

#include "Surface.h"
#include "Material.h"
#include "Intersection.h"


class Surface;

class Intersection;

class SceneObject {
private:
//    std::shared_ptr<Surface> surface;
    std::shared_ptr<Surface> surface;
    Material material;
public:
    SceneObject (std::shared_ptr<Surface> surface, Material material);


    [[nodiscard]] std::optional<Intersection> get_intersection (const Ray& ray) const;

    [[nodiscard]] Surface* getSurface () const;

    [[nodiscard]] const Material& getMaterial () const;
};



