//
// Created by kaappo on 11.3.2022.
//

#pragma once


#include "../light/Intensity.h"
#include "../geometry/Ray.h"

struct Interface {
    constexpr Interface () : ray{}, intensity{} {}
    constexpr Interface (const Ray& ray, const Intensity& intensity) : ray{ray}, intensity{intensity} {}

    Ray ray;
    Intensity intensity;
};



