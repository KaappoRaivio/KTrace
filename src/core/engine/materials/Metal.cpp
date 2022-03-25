//
// Created by kaappo on 11.3.2022.
//

#include <glm/gtx/norm.hpp>
#include <iostream>
#include "Metal.h"
#include "../../common/Intersection.h"
#include "../../geometry/Surface.h"
#include "../../light/IntensityBlend.h"
#include "Shading.h"


Metal::Metal (const Texture* albedo, const Texture* bump, double roughness) : Material(albedo, bump), roughness{roughness} {}

Metal::Metal (const Texture* albedo, double roughness) : Material(albedo), roughness{roughness} {}

Metal::Metal (double roughness) : Material(), roughness{roughness} {}

int Metal::scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, float currentOpticalDensity, std::array<Interface, 10>& scatteredRays) const {
    if (roughness == 1) return 0;


    const auto& reflected = glm::reflect(intersection.ray.getDirection(), normal);
    Intensity intensity = Intensity{(1 - roughness), (1 -roughness), (1 - roughness)};
    scatteredRays[0] = {{intersection.position, reflected}, intensity * albedo->getPixelAt(intersection.hitSurface->getUVAt(intersection.position))};
    return 1;
}

Intensity Metal::shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources, float currentOpticalDensity) const {
    const glm::vec3& d = intersection.ray.getDirection();
    const glm::vec3& R = glm::normalize(glm::reflect(d, normal));

    IntensityBlend diffuseShaded;
    IntensityBlend specularShaded;
    for (const auto& lightSource : visibleLightSources) {
        glm::vec3 vectorToLight = lightSource.position - intersection.position;
        const glm::vec3& V = glm::normalize(vectorToLight);

        float distanceCoefficient = 1.0 / glm::length2(vectorToLight);
        float diffuseDirectionCoefficient = Shading::lambertianDiffuseReflection(normal, V, d);
        float specularDirectionCoefficient = Shading::calculateBeckmannDistribution(R, V, roughness);

        diffuseShaded += lightSource.intensity * distanceCoefficient * diffuseDirectionCoefficient;
        specularShaded += lightSource.intensity * distanceCoefficient * specularDirectionCoefficient;
//        std::cout << "visible" << std::endl;
    }

    return (diffuseShaded.commitSum() * roughness + specularShaded.commitSum() * (1 - roughness))
           * albedo->getPixelAt(intersection.hitSurface->getUVAt(intersection.position));
}

std::ostream& Metal::print (std::ostream& s) const {
    return s << "Metal{" << roughness << ", " << *albedo << "}";
}


