//
// Created by kaappo on 7.5.2022.
//

#include "DebugMaterial.h"

int DebugMaterial::scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, float currentOpticalDensity, std::array<Interface, Config::MAX_SCATTER>& scatteredRays) const {
    return 0;
}

Intensity DebugMaterial::shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources, float currentOpticalDensity) const {
    return {1, 0, 0};
}

std::ostream& DebugMaterial::print (std::ostream& s) const {
    return s << "DebugMaterial{}";
}
