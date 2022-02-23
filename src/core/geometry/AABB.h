//
// Created by kaappo on 28.1.2022.
//

#pragma once


#include <ostream>
#include <glm/glm.hpp>
#include "Hittable.h"
#include "Ray.h"

class AABB {
private:
    glm::vec3 minimum, maximum;

public:
    AABB (const glm::vec3& minimum, const glm::vec3& maximum);
    constexpr AABB (bool invalid) : minimum{0, 0, 0}, maximum{0, 0, 0} {}

    bool operator== (const AABB& rhs) const;

    bool operator!= (const AABB& rhs) const;

    friend std::ostream& operator<< (std::ostream& os, const AABB& aabb);

    double getIntersectionDistance (const Ray& ray) const;

    AABB expand (const AABB& aabb);

    glm::vec3 getMinimum () const;
    glm::vec3 getMaximum () const;

    double intersects (const Ray& ray) const;
};
namespace AABBs {
    constexpr AABB INVALID{true};
}


