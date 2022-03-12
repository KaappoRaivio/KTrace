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

    Intensity getPixelAt (const glm::vec3& uv) const override;
};



