//
// Created by kaappo on 25.3.2022.
//

#include "Dielectric.h"
#include "../../geometry/Surface.h"
#include "../../common/MyVector3.h"
#include "../../common/mytypes.h"

int Dielectric::scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, float currentOpticalDensity, std::array<Interface, 10>& scatteredRays) const {

    float reflectance = Shading::getReflectance(std::abs(glm::dot(normal, intersection.ray.getDirection())), currentOpticalDensity / this->opticalDensity);
//    std::cout << glm::dot(normal, intersection.ray.getDirection()) << std::endl;
//    std::cout << reflectance << std::endl;

    int n = 0;
    if (reflectance > 0) {
        const auto& reflected = glm::reflect(intersection.ray.getDirection(), normal);
//        Intensity intensity = Intensity{(1 - roughness), (1 - roughness), (1 - roughness)} * alpha * reflectance;
        Intensity intensity = Intensity{1, 1, 1} * reflectance;
        scatteredRays[n++] = {{intersection.position, reflected}, intensity * albedo->getPixelAt(intersection.hitSurface->getUVAt(intersection.position))};
    }

    if (alpha < 1) {
        const auto& refracted = VectorOperations::refract(intersection.ray.getDirection(), normal, currentOpticalDensity / this->opticalDensity);
//        std::cout << refracted << std::endl;
        Intensity intensity = Intensity{1, 1, 1} * (1 - reflectance) * (1 - alpha);
//        std::cout << intensity << std::endl;
//        Intensity intensity = Intensity{1, 1, 1}  * 10;

        scatteredRays[n++] = {{intersection.position, refracted}, intensity * albedo->getPixelAt(intersection.hitSurface->getUVAt(intersection.position))};
    }

    return n;
}

Intensity Dielectric::shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources, float currentOpticalDensity) const {
    float reflectance = Shading::getReflectance(-glm::dot(normal, intersection.ray.getDirection()), currentOpticalDensity / this->opticalDensity);

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

    return (diffuseShaded.commitSum() * (1 - reflectance) + specularShaded.commitSum() * reflectance)
           * albedo->getPixelAt(intersection.hitSurface->getUVAt(intersection.position)) * alpha;

}

std::ostream& Dielectric::print (std::ostream& s) const {
    return s << "Dielectric{alpha: " << alpha << ", opticalDensity: " << opticalDensity << ", emittance: " << emittance << "}";
}
