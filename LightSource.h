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

    LightSource(const Vector3& position, const Intensity& intensity) : position{position}, intensity{intensity} {}
    LightSource& operator=(const LightSource& other) = default;
};





