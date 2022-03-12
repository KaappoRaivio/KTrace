//
// Created by kaappo on 9.2.2022.
//

#include "TextureManager.h"
#include "ImageTexture.h"
#include "SolidTexture.h"

const Texture* TextureManager::getImageTexture (std::string path) {
    std::unique_ptr<Texture> texture = std::make_unique<ImageTexture>(path);
    textures.push_back(std::move(texture));
    return textures[textures.size() - 1].get();
}

const Texture* TextureManager::getSolidTexture (Intensity color) {
    std::unique_ptr<Texture> texture = std::make_unique<SolidTexture>(color);
    textures.push_back(std::move(texture));
    return textures[textures.size() - 1].get();
}