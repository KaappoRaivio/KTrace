//
// Created by kaappo on 28.1.2022.
//

#pragma once

#include "Ray.h"
#include "../engine/Material.h"

class Surface;

class Hittable {
public:
    virtual double getIntersectionDistance (const Ray& ray, Surface*& hitSurface, const Material*& hitMaterial) = 0;
};