//
// Created by kaappo on 11.3.2022.
//

#pragma once


#include "../light/Intensity.h"
#include "../geometry/Ray.h"

struct Interface {
    constexpr Interface () : ray{}, intensity{} {}
    constexpr Interface (const Ray& ray, const Intensity& intensity) : Interface(ray, intensity, -1) {}
    constexpr Interface (const Ray& ray, const Intensity& intensity, float newOpticalDensity) : ray{ray}, intensity{intensity}, newOpticalDensity{newOpticalDensity} {}

    Ray ray;
    Intensity intensity;
    float newOpticalDensity;
};



