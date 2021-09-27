//
// Created by kaappo on 21.9.2021.
//

#include "SolidTexture.h"

SolidTexture::SolidTexture (const Intensity& intensity) : intensity(intensity) {}

Intensity SolidTexture::get_pixel_at (const Vector3& uv) const {
    return intensity;
}
