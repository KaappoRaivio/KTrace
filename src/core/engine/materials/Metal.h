//
// Created by kaappo on 11.3.2022.
//

#pragma once


#include "Material.h"

class Metal : public Material {
private:
    double roughness;


public:
    Metal (double roughness);

    std::vector<Interface> scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, std::stack<float>& opticalDensities) const override;
    Intensity shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources) const override;

};



