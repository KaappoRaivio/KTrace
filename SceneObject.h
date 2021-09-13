//
// Created by kaappo on 12.9.2021.
//

#pragma once


#include "Surface.h"
#include "Material.h"

class Surface;

class SceneObject {
private:
    const Surface& surface;
    const Material& material;
public:
    SceneObject(const Surface &surface, const Material &material);

    [[nodiscard]] const Surface &getSurface() const;
    [[nodiscard]] const Material &getMaterial() const;
};



