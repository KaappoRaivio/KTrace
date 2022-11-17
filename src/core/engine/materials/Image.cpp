//
// Created by kaappo on 21.9.2021.
//


#include <stdexcept>
#include <iostream>
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_FAILURE_STRINGS

#include "../../../../lib/stb/stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../../../../lib/stb/stb_image_write.h"
#include "../../common/mytypes.h"

Image::Image (const std::string& path) : width{0}, height{0} {
    int amountOfChannels = path.ends_with("jpg") ? 3 : 4;
    bool isHDR = path.ends_with("hdr");

//    data = stbi_loadf(path.c_str(), &width, &height, &bytes_per_pixel, amountOfChannels);
//    if (isHDR) {
//        hdrData = stbi_loadf(path.c_str(), &width, &height, &bytes_per_pixel, 0);
//    } else {
    data = stbi_load(path.c_str(), &width, &height, &bytes_per_pixel, 0);
//    }

    std::cout << "Initializing" << std::endl;
    if (width == 0 || height == 0) {
        std::cerr << path << std::endl;
        throw std::runtime_error("Error reading the image!");
    }

    std::cout << width << ", " << height << std::endl;
}

Image::~Image () {
    if constexpr(DEBUG) {
        std::cout << "Freed data!" << std::endl;
    }
    stbi_image_free(data);
}

Intensity Image::get_pixel_at (int x, int y) const {
    int index = bytes_per_pixel * (width * y + x);
    index %= width * height * bytes_per_pixel;
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

Image::Image (const std::vector<std::vector<Intensity>>& pixels) : width{static_cast<int>(pixels[0].size())}, height{static_cast<int>(pixels.size())} {
    std::cout << width << ", " << height << std::endl;
    data = (uint8_t*) malloc(width * height * 4);
    for (int y = 0 ; y < height ; ++y) {
        for (int x = 0 ; x < width ; ++x) {
            int index = (y * width + x) * 4;

            auto rgb = pixels[y][x].asRGB(2.0);

            data[index + 0] = rgb.r;
            data[index + 1] = rgb.g;
            data[index + 2] = rgb.b;
            data[index + 3] = 255;
        }
    }
    bytes_per_pixel = 4;
}

bool Image::save (const std::string& path) {
    return stbi_write_png(path.c_str(), width, height, bytes_per_pixel, data, 0);
}


ImageHDR::ImageHDR (const std::string& path) : width{0}, height{0} {
    std::cout << "paskda" << std::endl;
    int amountOfChannels = path.ends_with("jpg") ? 3 : 4;
    bool isHDR = path.ends_with("hdr");


    data = stbi_loadf(path.c_str(), &width, &height, &bytes_per_pixel, 0);

    std::cout << "Initializing" << bytes_per_pixel << std::endl;
    if (width == 0 || height == 0) {
        std::cerr << path << std::endl;
        throw std::runtime_error("Error reading the image!");
    }

    std::cout << width << ", " << height << std::endl;
}

Intensity ImageHDR::get_pixel_at (int x, int y) const {
    int index = bytes_per_pixel * (width * y + x);
    index %= width * height * bytes_per_pixel;
//    std::cout << data[0] << std::endl;
//    return {std::sqrt(data[index] / 256.0), std::sqrt(data[index + 1] / 256.0), std::sqrt(data[index + 2] / 256.0)};
//    return {data[index] / 256.0, data[index + 1] / 256.0, data[index + 2] / 256.0};
    return {data[index], data[index + 1], data[index + 2]};
}

ImageHDR::~ImageHDR () {
    if constexpr(DEBUG) {
        std::cout << "Freed data!" << std::endl;
    }
    stbi_image_free(data);
}

int ImageHDR::getWidth () const {
    return width;
}

int ImageHDR::getHeight () const {
    return height;
}


