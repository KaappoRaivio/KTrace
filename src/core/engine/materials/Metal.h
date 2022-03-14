//
// Created by kaappo on 11.3.2022.
//

#pragma once


#include "Material.h"

class Metal : public Material {
private:
    double roughness;


public:
    Metal (const Texture* bump, const Texture* albedo, double roughness);
    Metal (const Texture* albedo, double roughness);
    Metal (double roughness);

    std::vector<Interface> scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, std::stack<float>& opticalDensities) const override;
    Intensity shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources) const override;

    std::ostream& print (std::ostream& s) const override;
};



