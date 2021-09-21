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
    [[nodiscard]] virtual double get_intersection_distance (const Ray &ray) const = 0;
    [[nodiscard]] virtual Vector3 get_normal_at (const Vector3& position) const = 0;
    [[nodiscard]] virtual Vector3 get_uv_at (const Vector3& position) const = 0;
};



