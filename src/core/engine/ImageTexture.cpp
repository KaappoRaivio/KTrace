//
// Created by kaappo on 21.9.2021.
//

#include "ImageTexture.h"

ImageTexture::ImageTexture (const std::string& path) : image{path} {}

Intensity ImageTexture::getPixelAt (const MyVector3& uv) const {
//    std::cout << "uv " << uv << std::endl;

    double u = (uv.getI() - std::floor(uv.getI())) * image.getWidth();
    double v = (uv.getJ() - std::floor(uv.getJ())) * image.getHeight();

    return image.get_pixel_at(u, v);
//    return image.getPixelAt(image.getWidth() - 1 - std::floor(uv.getI() * image.getWidth() - 1e-9), image.getHeight() - 1 - std::floor(uv.getJ() * image.getHeight() - 1e-9));
}
