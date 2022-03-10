//
// Created by kaappo on 8.3.2022.
//
#include "mytypes.h"
#include <iostream>

std::ostream& operator << (std::ostream& cout, glm::vec3 vec) {
    return cout << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
}



//namespace MyRandom {
std::default_random_engine MyRandom::generator{MyRandom::SEED};
//}