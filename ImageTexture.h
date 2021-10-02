//
// Created by kaappo on 21.9.2021.
//

#pragma once


#include "Image.h"
#include "Texture.h"

class ImageTexture : public Texture {
private:
    Image image;
public:
    explicit ImageTexture (const std::string& path);

    Intensity get_pixel_at (const MyVector3& uv) const override;
};



