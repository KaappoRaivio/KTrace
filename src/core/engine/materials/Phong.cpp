//
// Created by kaappo on 11.4.2022.
//

#include <glm/gtx/norm.hpp>
#include "Phong.h"
#include "../../light/IntensityBlend.h"
#include "Shading.h"

#include "../../geometry/Surface.h"

int Phong::scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, float currentOpticalDensity, std::array<Interface, 10>& scatteredRays) const {
    return 0;
}

Intensity Phong::shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources, float currentOpticalDensity) const {

//    return {1, 0, 1};

    IntensityBlend diffuseShaded;
    IntensityBlend specularShaded;

    for (const auto& lightSource : visibleLightSources) {
        glm::vec3 vectorToLight = lightSource.position - intersection.position;
        const glm::vec3& L = glm::normalize(vectorToLight);

        const glm::vec3 V = glm::normalize(intersection.position - intersection.ray.getOrigin());


        float distanceCoefficient = 1.0 / glm::length2(vectorToLight);
        float diffuseDirectionCoefficient = Shading::lambertianDiffuseReflection(normal, L, intersection.ray.getDirection());
        float specularDirectionCoefficient = Shading::calculatePhongReflection(normal, L, V, specularPower);

        diffuseShaded += lightSource.intensity * distanceCoefficient * diffuseDirectionCoefficient;
        specularShaded += lightSource.intensity * distanceCoefficient * specularDirectionCoefficient;
//        std::cout << "visible" << std::endl;
    }

    const auto& uv = intersection.hitSurface->getUVAt(intersection.position);

    return diffuseShaded.commitSum() * albedoDiffuse->getPixelAt(uv) + specularShaded.commitSum() * albedoSpecular->getPixelAt(uv);// + albedoAmbient->getPixelAt(uv);
}

std::ostream& Phong::print (std::ostream& s) const {
    return s << "Phong{}";
}

Phong::Phong (const Texture* albedoAmbient, const Texture* albedoDiffuse, const Texture* albedoSpecular, float specularPower)
        : Material(&SolidTextures::WHITE), albedoAmbient(albedoAmbient), albedoDiffuse(albedoDiffuse), albedoSpecular(albedoSpecular), specularPower(specularPower) {

}
