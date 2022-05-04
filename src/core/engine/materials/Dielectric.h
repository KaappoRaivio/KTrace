//
// Created by kaappo on 25.3.2022.
//

#pragma once


#include <glm/gtx/norm.hpp>
#include "Material.h"
#include "../../light/IntensityBlend.h"
#include "Shading.h"
#include "../../../Config.h"

class Dielectric : public Material {
//private:
public:
    float absorbance;
    float opticalDensity;
    float roughness;

public:
    Dielectric (float roughness, float absorbance, float indexOfRefraction, const Texture* albedo, const Texture* bump, const Intensity& emittance);

    int scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, float currentOpticalDensity, std::array<Interface, Config::MAX_SCATTER>& scatteredRays) const override;
    Intensity shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources, float currentOpticalDensity) const override;
    std::ostream& print (std::ostream& s) const override;
};



