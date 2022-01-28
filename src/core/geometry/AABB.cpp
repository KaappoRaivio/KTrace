//
// Created by kaappo on 28.1.2022.
//

#include "AABB.h"
#include "Surface.h"

double AABB::getIntersectionDistance (const Ray& ray) const {
    if (!intersects(ray)) return 0;
    else return 1;
}

bool AABB::intersects (const Ray& ray) const {
    for (int a = 0 ; a < 3 ; a++) {
        auto invD = 1.0f / ray.getDirection()[a];
        auto t0 = (minimum[a] - ray.getOrigin()[a]) * invD;
        auto t1 = (maximum[a] - ray.getOrigin()[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);

        if (t1 <= t0)
            return false;
    }
    return true;
}

AABB::AABB (const MyVector3& minimum, const MyVector3& maximum) : minimum(minimum), maximum(maximum) {}

bool AABB::operator== (const AABB& rhs) const {
    return minimum == rhs.minimum &&
           maximum == rhs.maximum;
}

bool AABB::operator!= (const AABB& rhs) const {
    return !(rhs == *this);
}

AABB AABB::expand (const AABB& aabb) {
    MyVector3 newMinimum{std::min(minimum.getI(), aabb.minimum.getI()),
                         std::min(minimum.getJ(), aabb.minimum.getJ()),
                         std::min(minimum.getK(), aabb.minimum.getK())};

    MyVector3 newMaximum{std::max(maximum.getI(), aabb.maximum.getI()),
                         std::max(maximum.getJ(), aabb.maximum.getJ()),
                         std::max(maximum.getK(), aabb.maximum.getK())};

    return {newMinimum, newMaximum};

}

MyVector3 AABB::getMinimum () const {
    return minimum;
}

MyVector3 AABB::getMaximum () const {
    return maximum;
}

std::ostream& operator<< (std::ostream& os, const AABB& aabb) {
    os << "AABB{" << aabb.minimum << ", " << aabb.maximum << "}";
    return os;
}
