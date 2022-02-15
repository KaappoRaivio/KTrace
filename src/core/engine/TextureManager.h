//
// Created by kaappo on 9.2.2022.
//

#pragma once


#include <memory>
#include "Texture.h"

class TextureManager {
private:
    std::vector<std::unique_ptr<Texture>> textures;

public:
    const Texture* getImageTexture (std::string path);
    const Texture* getSolidTexture (Intensity color);
};



