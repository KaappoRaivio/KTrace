//
// Created by kaappo on 21.9.2021.
//

#pragma once

#include <string>
#include <vector>


#include "../../light/Intensity.h"


class Image {
private:
    int width, height, bytes_per_pixel;

    uint8_t* data;
public:
    explicit Image (const std::string& path);
    explicit Image (const std::vector<std::vector<Intensity>>& pixels);

    Intensity get_pixel_at (int x, int y) const;

    virtual ~Image ();

    int getWidth () const;

    int getHeight () const;

    bool save (const std::string& path);
};

class ImageHDR {
private:
    int width, height, bytes_per_pixel;

    float* data;
public:
    explicit ImageHDR (const std::string& path);

    Intensity get_pixel_at (int x, int y) const;

    virtual ~ImageHDR ();

    int getWidth () const;
    int getHeight () const;
};



//int main () {
////    std::cout << "Hello, world!" << std::endl;
//    Image image{std::string{"../res/texture1.png"}};
//    const Intensity& intensity = image.getPixelAt(0, 0);
//    std::cout << intensity << std::endl;
//}
