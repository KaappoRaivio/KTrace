//
// Created by kaappo on 11.9.2021.
//

#pragma once

#include <optional>

#include "Ray.h"
#include "Intersection.h"

class Surface {
public:
    // if doesn't intersect, return 0.
    virtual double get_intersection_distance (const Ray& ray) const = 0;

    virtual MyVector3 get_normal_at (const MyVector3& position) const = 0;

    virtual MyVector3 get_uv_at (const MyVector3& position) const = 0;
};



