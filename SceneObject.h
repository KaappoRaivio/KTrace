//
// Created by kaappo on 12.9.2021.
//

#pragma once

#include <memory>
#include <ostream>

#include "Surface.h"
#include "Material.h"
#include "Intersection.h"


class Surface;

class Intersection;

class SceneObject {
private:
public:
    friend std::ostream& operator<< (std::ostream& os, const SceneObject& object);

private:
//    std::shared_ptr<Surface> surface;
    std::shared_ptr<Surface> surface;
    Material material;
public:
    SceneObject (std::shared_ptr<Surface> surface, Material material);


    std::optional<Intersection> get_intersection (const Ray& ray) const;

    Surface* getSurface () const;

    const Material& getMaterial () const;
};



