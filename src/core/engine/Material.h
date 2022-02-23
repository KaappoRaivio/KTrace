//
// Created by kaappo on 12.9.2021.
//

#pragma once

#include <memory>
#include <ostream>
#include <glm/glm.hpp>
#include "../light/Intensity.h"
#include "Texture.h"
#include "SolidTexture.h"

struct Material {
    const Texture* albedo;
    const Texture* bump;
    double glossiness;
    double alpha = 1;
    double opticalDensity = 1;

    constexpr Material (const Texture* const albedo, double glossiness, const Texture* bump) : albedo{albedo}, bump{bump}, glossiness{glossiness} {}
    constexpr Material (const Texture* const albedo, double glossiness, double alpha) : albedo{albedo}, bump{&SolidTextures::BUMP_UP}, glossiness{glossiness}, alpha{alpha} {}
    explicit Material (const Texture* const albedo) : albedo{albedo}, bump{&SolidTextures::BUMP_UP}, glossiness{0}, alpha{1} {}

public:
    Intensity getAlbedoAt (const glm::vec3& uv) const;

    glm::vec3 getBumpAt (const glm::vec3& uv, const glm::vec3& normal) const;

    friend std::ostream& operator<< (std::ostream& os, const Material& material);
};


namespace Materials {
    constexpr Material WHITE_GLOSSY{&SolidTextures::WHITE, 0.8, 1};
    constexpr Material BLUE_GLOSSY{&SolidTextures::BLUE, 0.8, 1};
    constexpr Material BLUE{&SolidTextures::BLUE, 0, 1};
    constexpr Material RED_GLOSSY{&SolidTextures::RED, 0.6, 1};
//    constexpr Material BLUE_GLOSSY{&SolidTextures::BLUE, 0.8};
    constexpr Material YELLOW_GLOSSY{&SolidTextures::YELLOW, 0.8, 1};
    constexpr Material GREEN_GLOSSY{&SolidTextures::GREEN, 0.8, 1};
    constexpr Material WHITE{&SolidTextures::WHITE, 0, 1};
}