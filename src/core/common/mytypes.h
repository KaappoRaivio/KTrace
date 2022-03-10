//
// Created by kaappo on 28.1.2022.
//

#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <array>
#include <random>


constexpr bool DEBUG = false;

constexpr double PRECISION_LIMIT = 0.001;

namespace MyRandom {
    constexpr unsigned SEED = 0xCAFEBABE;
    extern std::default_random_engine generator;
}


std::ostream& operator << (std::ostream& cout, glm::vec3 vec);