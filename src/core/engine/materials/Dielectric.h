//
// Created by kaappo on 25.3.2022.
//

#pragma once


#include <glm/gtx/norm.hpp>
#include "Material.h"
#include "../../light/IntensityBlend.h"
#include "Shading.h"

class Dielectric : public Material {
private:
    double alpha;
    double opticalDensity;
    double roughness;

public:
    template <class... Types>
    Dielectric (double roughness, double alpha, double indexOfRefraction, Types... args) : Material(args...), alpha{alpha}, opticalDensity{indexOfRefraction}, roughness{roughness} {}
    template <class... Types>
    Dielectric (double roughness, double alpha, Types... args) : Dielectric(roughness, alpha, 1.0, args...) {}
    template <class... Types>
    Dielectric (double roughness, Types... args) : Dielectric{roughness, 1.0, args...} {}

    int scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, float currentOpticalDensity, std::array<Interface, 10>& scatteredRays) const override;
    Intensity shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources) const override;
    std::ostream& print (std::ostream& s) const override;
};



