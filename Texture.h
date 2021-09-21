//
// Created by kaappo on 21.9.2021.
//

#pragma once


#include "Intensity.h"
#include "Vector3.h"

class Texture {
public:
    [[nodiscard]] virtual Intensity get_pixel_at (const Vector3& uv) const = 0;
};



