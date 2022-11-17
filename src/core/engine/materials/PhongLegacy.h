//
// Created by kaappo on 7.5.2022.
//

#pragma once


#include "Phong.h"

class PhongLegacy : public Phong {
    float glossiness;
public:
    PhongLegacy (const Texture* albedoDiffuse, float glossiness);

    int scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, float currentOpticalDensity, std::array<Interface, Config::MAX_SCATTER>& scatteredRays) const override;

    Intensity shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources, float currentOpticalDensity) const override;

};



