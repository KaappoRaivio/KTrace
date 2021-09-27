//
// Created by kaappo on 21.9.2021.
//

#pragma once


#include "Texture.h"

class SolidTexture : public Texture {
private:
    Intensity intensity;
public:
    explicit SolidTexture (const Intensity& intensity);

public:
    [[nodiscard]] Intensity get_pixel_at (const Vector3& uv) const override;
};



