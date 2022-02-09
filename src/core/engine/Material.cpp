//
// Created by kaappo on 21.9.2021.
//

#include "Material.h"

Intensity Material::getAlbedoAt (const MyVector3& uv) const {
//    return (*albedo).getPixelAt(uv);
    return albedo->getPixelAt(uv);
}

std::ostream& operator<< (std::ostream& os, const Material& material) {
    os << "albedo: " << material.albedo << " glossiness: " << material.glossiness;
    return os;
}

MyVector3 Material::getBumpAt (const MyVector3& uv, const MyVector3& normal) const {
    const Intensity& intensity = bump->getPixelAt(uv);

    MyVector3 originBump {intensity.r() - 0.5, intensity.g() - 0.5, intensity.b()};

    const auto& newSide = normal.cross(MyVector3s::UP);
    const auto& newOut = newSide.cross(normal);
    const auto& newUp = normal;

    return newSide * originBump.getI() + newOut * originBump.getJ() + newUp * originBump.getK();
}
