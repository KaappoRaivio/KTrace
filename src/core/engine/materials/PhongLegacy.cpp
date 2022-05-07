//
// Created by kaappo on 7.5.2022.
//

#include <glm/gtx/norm.hpp>
#include "PhongLegacy.h"
#include "Shading.h"
#include "../../light/IntensityBlend.h"
#include "../../geometry/Surface.h"

int PhongLegacy::scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, float currentOpticalDensity, std::array<Interface, Config::MAX_SCATTER>& scatteredRays) const {
    const auto& reflected = glm::reflect(intersection.ray.getDirection(), normal);
    scatteredRays[0] = {{intersection.position, reflected}, albedoSpecular->getPixelAt(intersection.hitSurface->getUVAt(position))};
    return 1;
}

PhongLegacy::PhongLegacy (const Texture* albedoAmbient, const Texture* albedoDiffuse, const Texture* albedoSpecular, const Texture* albedoFresnel, float specularPower) : Phong(albedoAmbient, albedoDiffuse, albedoSpecular, albedoFresnel, specularPower) {}

Intensity PhongLegacy::shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources, float currentOpticalDensity) const {
    //    return {1, 0, 1};

    IntensityBlend diffuseShaded;
    IntensityBlend specularShaded;
    IntensityBlend fresnelShaded;

    for (const auto& lightSource : visibleLightSources) {
        glm::vec3 vectorToLight = lightSource.position - intersection.position;
        const glm::vec3& L = glm::normalize(vectorToLight);

        const glm::vec3 V = glm::normalize(intersection.position - intersection.ray.getOrigin());


        float distanceCoefficient = 1.0 / glm::length2(vectorToLight);
        float diffuseDirectionCoefficient = Shading::lambertianDiffuseReflection(normal, L, intersection.ray.getDirection());
//        float specularDirectionCoefficient = Shading::calculatePhongReflection(normal, L, V, specularPower);

        const auto reflectance = Shading::getReflectance(-glm::dot(normal, V), 2);
//        std::cout << glm::length(normal) << ", " << reflectance << std::endl;

//        fresnelShaded += lightSource.intensity * distanceCoefficient * reflectance * specularDirectionCoefficient;
//        diffuseShaded += lightSource.intensity * distanceCoefficient * diffuseDirectionCoefficient * (1 - reflectance);
        diffuseShaded += lightSource.intensity * distanceCoefficient * diffuseDirectionCoefficient;
//        specularShaded += lightSource.intensity * distanceCoefficient * specularDirectionCoefficient;
//        std::cout << "visible" << std::endl;
    }

    const auto& uv = intersection.hitSurface->getUVAt(intersection.position);



    return diffuseShaded.commitSum() * albedoDiffuse->getPixelAt(uv) * (1 - albedoSpecular->getPixelAt(uv).getBrightness()) + specularShaded.commitSum() * albedoSpecular->getPixelAt(uv) + fresnelShaded.commitSum() * albedoFresnel->getPixelAt(uv);// + albedoAmbient->getPixelAt(uv);
}
