//
// Created by kaappo on 21.9.2021.
//


#include <stdexcept>
#include <iostream>
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_FAILURE_STRINGS

#include "lib/stb/std_image.h"

Image::Image (const std::string& path) : width{0}, height{0}, bytes_per_pixel{0} {
    int amountOfChannels = path.ends_with("jpg") ? 3 : 4;

    data = stbi_load(path.c_str(), &width, &height, &bytes_per_pixel, amountOfChannels);
    std::cout << "Initializing" << std::endl;
    if (width == 0 || height == 0) {
        std::cerr << path << std::endl;
        throw std::runtime_error("Error reading the image!");
    }

    std::cout << width << ", " << height << std::endl;
}

Image::~Image () {
    std::cout << "Freed data!" << std::endl;
    stbi_image_free(data);
}

Intensity Image::get_pixel_at (int x, int y) const {
    int index = bytes_per_pixel * (width * y + x);
//    std::cout << data[0] << std::endl;
//    return {std::sqrt(data[index] / 256.0), std::sqrt(data[index + 1] / 256.0), std::sqrt(data[index + 2] / 256.0)};
    return {data[index] / 256.0, data[index + 1] / 256.0, data[index + 2] / 256.0};
//    return {1, 1, 0};
//    return {std::sqrt(data[index] / 256.0), std::sqrt(data[index + 1] / 256.0), std::sqrt(data[index + 2] / 256.0)};
}

int Image::getWidth () const {
    return width;
}

int Image::getHeight () const {
    return height;
}


