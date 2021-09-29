//
// Created by kaappo on 12.9.2021.
//

#pragma once

#include <memory>
#include "Vector3.h"
#include "Intensity.h"
#include "Texture.h"

struct Material {
    std::shared_ptr<Texture> albedo;
    double glossiness;

    Material (std::shared_ptr<Texture> albedo, double glossiness) : albedo{albedo}, glossiness{glossiness} {}

    explicit Material (std::shared_ptr<Texture> albedo) : albedo{albedo}, glossiness{0} {}

public:
    Intensity get_albedo_at (const Vector3& uv) const;
};