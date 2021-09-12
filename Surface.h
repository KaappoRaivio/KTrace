//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include "Ray.h"

class Surface {
public:
    // if doesn't intersect, return 0.
    [[nodiscard]] virtual double get_intersection_distance (const Ray &ray) const = 0;
};



