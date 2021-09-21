//
// Created by kaappo on 21.9.2021.
//

#include "Material.h"

Intensity Material::get_albedo_at(const Vector3 &uv) const {
    return albedo->get_pixel_at(uv);
}

