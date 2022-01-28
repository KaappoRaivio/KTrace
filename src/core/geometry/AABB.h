//
// Created by kaappo on 28.1.2022.
//

#pragma once


#include "../common/MyVector3.h"
#include "Hittable.h"
#include "Ray.h"

class AABB {
private:
    MyVector3 minimum, maximum;
public:
    AABB (const MyVector3& minimum, const MyVector3& maximum);
    constexpr AABB (bool invalid) : maximum{0, 0, 0}, minimum{0, 0, 0} {

    }

private:

    bool intersects (const Ray& ray) const;

public:
    double getIntersectionDistance (const Ray& ray) const;
};
namespace AABBs {
    constexpr AABB INVALID{true};
}


