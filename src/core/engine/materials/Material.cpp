//
// Created by kaappo on 21.9.2021.
//

#include "Material.h"

Intensity Material::getAlbedoAt (const glm::vec3& uv) const {
//    return (*albedo).getPixelAt(uv);
    return albedo->getPixelAt(uv);
}

glm::vec3 Material::getNormalAt (const glm::vec3& uv, const glm::vec3& normal) const {
//    return bump->getPixelAt(uv);
        const Intensity& intensity = bump->getPixelAt(uv);

    glm::vec3 originBump{intensity.r() - 0.5, intensity.g() - 0.5, intensity.b()};

//    const auto& newSide = -normal.cross(glm::vec3s::UP);
    const auto& newSide = -glm::cross(normal, {0, 0, 1});
    const auto& newOut = glm::cross(newSide, normal);
    const auto& newUp = normal;

    return newSide * (originBump.x * 1.0f) + newOut * (originBump.y * 1.0f) + newUp * originBump.z;
}

Material::Material (const Texture* albedo, const Texture* bump, const Intensity& emittance) : albedo(albedo), bump(bump), emittance(emittance) {}
Material::Material (const Texture* albedo, const Texture* bump) : Material{albedo, bump, {0, 0, 0}} {}
Material::Material (const Texture* albedo) : Material{albedo, &SolidTextures::BUMP_UP} {}
Material::Material () : Material{&SolidTextures::WHITE} {}

//glm::vec3 Material::getBumpAt (const glm::vec3& uv, const glm::vec3& normal) const {
//    const Intensity& intensity = bump->getPixelAt(uv);
//
//    glm::vec3 originBump{intensity.r() - 0.5, intensity.g() - 0.5, intensity.b()};
//
////    const auto& newSide = -normal.cross(glm::vec3s::UP);
//    const auto& newSide = -glm::cross(normal, {0, 0, 1});
//    const auto& newOut = glm::cross(newSide, normal);
//    const auto& newUp = normal;
//
//    return newSide * (originBump.x * 1.0f) + newOut * (originBump.y * 1.0f) + newUp * originBump.z;
//}

std::ostream& operator<< (std::ostream& os, const Material& material) {
    return material.print(os);
}

