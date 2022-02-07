//
// Created by kaappo on 21.9.2021.
//

#include "Material.h"

Intensity Material::get_albedo_at (const MyVector3& uv) const {
//    return (*albedo).get_pixel_at(uv);
    return albedo->get_pixel_at(uv);
}

std::ostream& operator<< (std::ostream& os, const Material& material) {
    os << "albedo: " << material.albedo << " glossiness: " << material.glossiness;
    return os;
}

namespace Materials {
//    extern const Material WHITE{&SolidTextures::WHITE, 0.8};
}