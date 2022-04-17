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
private:
    float alpha;
    float opticalDensity;
    float roughness;

public:
    template <class... Types>
    Dielectric (float roughness, float alpha, float indexOfRefraction, Types... args) : Material(args...), alpha{alpha}, opticalDensity{indexOfRefraction}, roughness{roughness} {}
    template <class... Types>
    Dielectric (float roughness, float alpha, Types... args) : Dielectric(roughness, alpha, 1.0, args...) {}
    template <class... Types>
    Dielectric (float roughness, Types... args) : Dielectric{roughness, 1.0f, args...} {}

    int scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, float currentOpticalDensity, std::array<Interface, Config::MAX_SCATTER>& scatteredRays) const override;
    Intensity shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources, float currentOpticalDensity) const override;
    std::ostream& print (std::ostream& s) const override;
};



