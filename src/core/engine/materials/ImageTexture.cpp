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

std::ostream& ImageTexture::print (std::ostream& cout) const {
    return cout << "ImageTexture";
}

namespace ImageTextures {
    const ImageTexture DEBUG_TEXTURE {"../res/texture3.png"};
}

ImageTextureHDR::ImageTextureHDR (const std::string& path) : image{path} {

}

Intensity ImageTextureHDR::getPixelAt (const glm::vec3& uv) const {
    double u = (uv.x - std::floor(uv.x)) * image.getWidth();
    double v = (uv.y - std::floor(uv.y)) * image.getHeight();

    return image.get_pixel_at(u, v);
}

std::ostream& ImageTextureHDR::print (std::ostream& cout) const {
    return cout << "ImageTextureHDR";
}
