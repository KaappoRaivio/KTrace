//
// Created by kaappo on 21.9.2021.
//

#pragma once


#include "Intensity.h"
#include "MyVector3.h"

class Texture {
public:
    virtual Intensity get_pixel_at (const MyVector3& uv) const = 0;
};



