//
// Created by kaappo on 11.3.2022.
//

#pragma once


#include "Material.h"

class Metal : public Material {
private:
    double roughness;

public:
    Metal (const Texture* albedo, const Texture* bump, double roughness);
    Metal (const Texture* albedo, double roughness);
    Metal (double roughness);

    int scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, float currentOpticalDensity, std::array<Interface, 10>& out_scatteredRays) const override;
    Intensity shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources) const override;

    std::ostream& print (std::ostream& s) const override;
};



