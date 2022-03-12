//
// Created by kaappo on 28.1.2022.
//

#pragma once

#include "Ray.h"
#include "../engine/materials/Material.h"
#include "../common/Intersection.h"

class Surface;

class Hittable {
public:
    virtual bool getIntersectionDistance (const Ray& ray, Intersection& out) const = 0;
};