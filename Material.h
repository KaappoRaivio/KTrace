//
// Created by kaappo on 12.9.2021.
//

#pragma once

#include "Vector3.h"
#include "Intensity.h"

struct Material {
    Intensity albedo;
    double glossiness;

    Material (const Intensity &albedo, double glossiness) : albedo{albedo}, glossiness{glossiness} {}
    explicit Material (const Intensity &albedo) : albedo{albedo}, glossiness{0} {}
};