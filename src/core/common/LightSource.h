//
// Created by kaappo on 13.9.2021.
//

#include <utility>
#include <ostream>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "../light/Intensity.h"

#pragma once


struct LightSource {
    glm::vec3 position;
    Intensity intensity;
    double radius;

    constexpr LightSource (glm::vec3 position, const Intensity& intensity, double radius) : position{std::move(position)}, intensity{intensity}, radius{radius} {}

//    LightSource& operator= (const LightSource& other) = default;

    friend std::ostream& operator<< (std::ostream& os, const LightSource& source) {
        os << "position: " << glm::to_string(source.position) << " intensity: " << source.intensity << " radius: " << source.radius;
        return os;
    }
};





