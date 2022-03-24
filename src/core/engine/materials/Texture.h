//
// Created by kaappo on 21.9.2021.
//

#pragma once


#include "../../light/Intensity.h"
#include <glm/glm.hpp>
#include <ostream>

class Texture {
public:
    virtual Intensity getPixelAt (const glm::vec3& uv) const = 0;
    virtual std::ostream& print (std::ostream& cout) const = 0;

    friend std::ostream& operator<< (std::ostream& os, const Texture& texture);
};



