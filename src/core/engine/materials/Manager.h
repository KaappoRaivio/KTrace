//
// Created by kaappo on 9.2.2022.
//

#pragma once


#include <memory>
#include <vector>
#include "Texture.h"

template <typename T>
class Manager {
private:
    std::vector<std::unique_ptr<T>> objects;

public:
    template<typename Subclass, typename... Types>
    const T* get (Types&&... args) {
        std::unique_ptr<T> instance = std::make_unique<Subclass>(std::forward<Types>(args)...);
        objects.push_back(std::move(instance));
        return objects[objects.size() - 1].get();
    }
//    const Texture* getImageTexture (std::string path);
//    const Texture* getSolidTexture (Intensity color);
};



