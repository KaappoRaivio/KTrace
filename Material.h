//
// Created by kaappo on 12.9.2021.
//

#pragma once

#include "Vector3.h"
#include "Intensity.h"
#include "Texture.h"

struct Material {
    Texture* albedo;
    double glossiness;

    Material (Texture* albedo, double glossiness) : albedo{albedo}, glossiness{glossiness} {}
    explicit Material (Texture* albedo) : albedo{albedo}, glossiness{0} {}

public:
    [[nodiscard]] Intensity get_albedo_at (const Vector3& uv) const;
};