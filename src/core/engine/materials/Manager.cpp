//
// Created by kaappo on 9.2.2022.
//

#include "Manager.h"
#include "ImageTexture.h"
#include "SolidTexture.h"

//const Texture* Manager::getImageTexture (std::string path) {
//    std::unique_ptr<Texture> texture = std::make_unique<ImageTexture>(path);
//    objects.push_back(std::move(texture));
//    return objects[objects.size() - 1].get();
//}
//
//const Texture* Manager::getSolidTexture (Intensity color) {
//    std::unique_ptr<Texture> texture = std::make_unique<SolidTexture>(color);
//    objects.push_back(std::move(texture));
//    return objects[objects.size() - 1].get();
//}