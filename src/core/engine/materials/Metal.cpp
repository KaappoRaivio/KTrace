//
// Created by kaappo on 11.3.2022.
//

#include <glm/gtx/norm.hpp>
#include "Metal.h"
#include "../../common/Intersection.h"
#include "../../geometry/Surface.h"
#include "../../light/IntensityBlend.h"
#include "Shading.h"


Metal::Metal (double roughness) : roughness{roughness} {}

std::vector<Interface> Metal::scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, std::stack<float>& opticalDensities) const {
    std::vector<Interface> interfaces{1};
    const auto& reflected = glm::reflect(intersection.ray.getDirection(), normal);
    const Intensity& attenuation = albedo->getPixelAt(intersection.hitSurface->getUVAt(intersection.position));
    interfaces.push_back({Ray{intersection.ray.getOrigin(), reflected}, attenuation});
    return interfaces;
//    return std::vector<Interface>();
}

Intensity Metal::shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources) const {
    const glm::vec3& d = intersection.ray.getDirection();
    const glm::vec3& R = glm::normalize(glm::reflect(d, normal));

    IntensityBlend diffuseShaded;
    for (const auto& lightSource : visibleLightSources) {
        glm::vec3 vectorToLight = lightSource.position - intersection.position;
        const glm::vec3& V = glm::normalize(vectorToLight);

        float distanceCoefficient = 1.0 / glm::length2(vectorToLight);
        float diffuseDirectionCoefficient = Shading::lambertianDiffuseReflection(normal, V, d);
//        float specularDirectionCoefficient = Shading::calculateBeckmannDistribution(R, V, roughness);

        diffuseShaded += lightSource.intensity / distanceCoefficient * diffuseDirectionCoefficient;
    }

    return diffuseShaded.commitBlend() * roughness * albedo->getPixelAt(intersection.hitSurface->getUVAt(intersection.position));
}


