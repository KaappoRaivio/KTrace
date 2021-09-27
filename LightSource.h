//
// Created by kaappo on 13.9.2021.
//

#include <utility>

#include "Vector3.h"
#include "Intensity.h"

#pragma once


struct LightSource {
    Vector3 position;
    Intensity intensity;
    double radius;

    LightSource (Vector3 position, const Intensity& intensity, double radius) : position{std::move(position)}, intensity{intensity}, radius{radius} {}

    LightSource& operator= (const LightSource& other) = default;
};





