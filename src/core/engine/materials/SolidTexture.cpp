//
// Created by kaappo on 21.9.2021.
//

#include "SolidTexture.h"


Intensity SolidTexture::getPixelAt (const glm::vec3& uv) const {
    return intensity;
}

std::ostream& SolidTexture::print (std::ostream& cout) const {
    return cout << "SolidTexture{" << intensity << "}";
}

SolidTexture operator* (double t, const SolidTexture& texture) {
    return SolidTexture{texture.intensity * t};
}
