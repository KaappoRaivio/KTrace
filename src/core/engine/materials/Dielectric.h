//
// Created by kaappo on 25.3.2022.
//

#pragma once


#include "Material.h"

class Dielectric : public Material {
private:
    double alpha;
    double indexOfRefraction;
    double roughness;

public:
    template <typename Types>
    Dielectric (double roughness, double alpha, double indexOfRefraction, Types args...) : Material(args), alpha{alpha}, indexOfRefraction{indexOfRefraction}, roughness{roughness} {}
    template <typename Types>
    Dielectric (double roughness, double alpha, Types args...) : Dielectric(roughness, alpha, 1.0, args) {}
    template <typename Types>
    Dielectric (double roughness, Types args...) : Dielectric{roughness, 1.0, args} {}

    int scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, std::stack<float>& opticalDensities, std::array<Interface, 10>& scatteredRays) const override;

    }

    Intensity shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources) const override {
        return Intensity();
    }

    std::ostream& print (std::ostream& s) const override {
        return s << "Dielectric{alpha: " << alpha << ", indexOfRefraction: " << indexOfRefraction << "}";
    }
};



