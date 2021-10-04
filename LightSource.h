//
// Created by kaappo on 13.9.2021.
//

#include <utility>
#include <ostream>

#include "MyVector3.h"
#include "Intensity.h"

#pragma once


struct LightSource {
    MyVector3 position;
    Intensity intensity;
    double radius;

    LightSource (MyVector3 position, const Intensity& intensity, double radius) : position{std::move(position)}, intensity{intensity}, radius{radius} {}

    LightSource& operator= (const LightSource& other) = default;

    friend std::ostream& operator<< (std::ostream& os, const LightSource& source) {
        os << "position: " << source.position << " intensity: " << source.intensity << " radius: " << source.radius;
        return os;
    }
};





