//
// Created by kaappo on 25.3.2022.
//

#include "Dielectric.h"
#include "../../geometry/Surface.h"

int Dielectric::scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, std::stack<float>& opticalDensities, std::array<Interface, 10>& scatteredRays) const {

    int n = 0;
    if (roughness < 1) {
        const auto& reflected = glm::reflect(intersection.ray.getDirection(), normal);
        Intensity intensity = Intensity{(1 - roughness), (1 - roughness), (1 - roughness)};
        scatteredRays[n++] = {{intersection.position, reflected}, intensity * albedo->getPixelAt(intersection.hitSurface->getUVAt(intersection.position))};
    }

    if (alpha < 1) {

    }
}
