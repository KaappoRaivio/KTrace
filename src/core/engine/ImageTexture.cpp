//
// Created by kaappo on 21.9.2021.
//

#include "ImageTexture.h"

ImageTexture::ImageTexture (const std::string& path) : image{path} {}

Intensity ImageTexture::getPixelAt (const glm::vec3& uv) const {
//    std::cout << "uv " << uv << std::endl;

    double u = (uv.x - std::floor(uv.x)) * image.getWidth();
    double v = (uv.y - std::floor(uv.y)) * image.getHeight();

    return image.get_pixel_at(u, v);
//    return image.getPixelAt(image.getWidth() - 1 - std::floor(uv.x * image.getWidth() - 1e-9), image.getHeight() - 1 - std::floor(uv.y * image.getHeight() - 1e-9));
}
