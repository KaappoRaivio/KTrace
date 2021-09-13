//
// Created by kaappo on 13.9.2021.
//

#include <utility>

#include "Vector3.h"
#include "Intensity.h"

#pragma once


struct LightSource {
    const Vector3 position;
    const Intensity intensity;

    LightSource(Vector3 position, Intensity intensity) : position{std::move(position)}, intensity{std::move(intensity)} {}
};



