//
// Created by kaappo on 12.9.2021.
//

#include "SceneObject.h"

SceneObject::SceneObject(const Surface &surface, const Material &material) : surface(surface), material(material) {}

const Surface &SceneObject::getSurface() const {
    return surface;
}

const Material &SceneObject::getMaterial() const {
    return material;
}
