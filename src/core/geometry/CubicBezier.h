//
// Created by kaappo on 5.3.2022.
//

#pragma once


#include <glm/vec3.hpp>
#include "Ray.h"

class CubicBezier {
private:
    glm::vec3 p0, p1, p2, p3;
public:
    CubicBezier (const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);

    Ray apply (double t);
};



