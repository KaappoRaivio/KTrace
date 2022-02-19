//
// Created by kaappo on 21.9.2021.
//

#include "Material.h"

Intensity Material::getAlbedoAt (const glm::vec3& uv) const {
//    return (*albedo).getPixelAt(uv);
    return albedo->getPixelAt(uv);
}

std::ostream& operator<< (std::ostream& os, const Material& material) {
    os << "albedo: " << material.albedo << " glossiness: " << material.glossiness;
    return os;
}

glm::vec3 Material::getBumpAt (const glm::vec3& uv, const glm::vec3& normal) const {
    const Intensity& intensity = bump->getPixelAt(uv);

    glm::vec3 originBump {intensity.r() - 0.5, intensity.g() - 0.5, intensity.b()};

//    const auto& newSide = -normal.cross(glm::vec3s::UP);
    const auto& newSide = -glm::cross(normal, {0, 0, 1});
    const auto& newOut = glm::cross(newSide, normal);
    const auto& newUp = normal;

    return newSide * (originBump.x * 1.0f) + newOut * (originBump.y * 1.0f) + newUp * originBump.z;
}
