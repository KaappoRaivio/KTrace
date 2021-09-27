//
// Created by kaappo on 21.9.2021.
//

#include "ImageTexture.h"

ImageTexture::ImageTexture (const std::string& path) : image{path} {}

Intensity ImageTexture::get_pixel_at (const Vector3& uv) const {
    return image.get_pixel_at(std::floor(uv.getI() * image.getWidth()), std::floor(uv.getJ() * image.getHeight()));
}
