//
// Created by kaappo on 21.9.2021.
//


#include <stdexcept>
#include <iostream>
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_FAILURE_STRINGS
#include "lib/stb/std_image.h"

Image::Image(const std::string& path) : width{0}, height{0}, bytes_per_pixel{0} {
    data = stbi_load(path.c_str(), &width, &height, &bytes_per_pixel, 4);
    if (width == 0 || height == 0) {
        throw std::runtime_error("Error reading the image!");
    }

    std::cout << width << ", " << height << std::endl;
}

Image::~Image() {
    stbi_image_free(data);
    std::cout << "Freed data!" << std::endl;
}

Intensity Image::get_pixel_at(int x, int y) const {
    int index = bytes_per_pixel * (width * y + x);
    return {std::sqrt(data[index] / 256.0), std::sqrt(data[index + 1] / 256.0), std::sqrt(data[index + 2] / 256.0)};
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}


