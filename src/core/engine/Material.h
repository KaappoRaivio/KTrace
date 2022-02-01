//
// Created by kaappo on 12.9.2021.
//

#pragma once

#include <memory>
#include <ostream>
#include "../common/MyVector3.h"
#include "../light/Intensity.h"
#include "Texture.h"
#include "SolidTexture.h"

struct Material {
    const Texture* albedo;
    double glossiness;

    Material (const Texture* const albedo, double glossiness) : albedo{albedo}, glossiness{glossiness} {}
    explicit Material (const Texture* const albedo) : albedo{albedo}, glossiness{0} {}

    Material(const Material& other) = delete;
    void operator=(const Material& other) = delete;

public:
    Intensity get_albedo_at (const MyVector3& uv) const;

    friend std::ostream& operator<< (std::ostream& os, const Material& material);
};


namespace Materials {
    extern const Material WHITE;
}