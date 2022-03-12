//
// Created by kaappo on 21.9.2021.
//

#pragma once


#include "../../light/Intensity.h"
#include <glm/glm.hpp>

class Texture {
public:
    virtual Intensity getPixelAt (const glm::vec3& uv) const = 0;
};



