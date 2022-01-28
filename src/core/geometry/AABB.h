//
// Created by kaappo on 28.1.2022.
//

#pragma once


#include <ostream>
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

    bool operator== (const AABB& rhs) const;

    bool operator!= (const AABB& rhs) const;

    friend std::ostream& operator<< (std::ostream& os, const AABB& aabb);

    double getIntersectionDistance (const Ray& ray) const;

    AABB expand (const AABB& aabb);

    MyVector3 getMinimum () const;
    MyVector3 getMaximum () const;

    bool intersects (const Ray& ray) const;
};
namespace AABBs {
    constexpr AABB INVALID{true};
}


