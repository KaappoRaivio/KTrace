//
// Created by kaappo on 28.1.2022.
//

#include "AABB.h"
#include "Surface.h"

double AABB::getIntersectionDistance (const Ray& ray) const {
    return intersects(ray);
//    if (!intersects(ray)) return 0;
//    else return 1;
}

double AABB::intersects (const Ray& ray) const {
    auto d_inv = MyVector3{1 / ray.getDirection().getI(), 1 / ray.getDirection().getJ(), 1 / ray.getDirection().getK()};

    double tx1 = (minimum.getI() - ray.getOrigin().getI()) * d_inv.getI();
    double tx2 = (maximum.getI() - ray.getOrigin().getI()) * d_inv.getI();

    double tmin = std::min(tx1, tx2);
    double tmax = std::max(tx1, tx2);

    double ty1 = (minimum.getJ() - ray.getOrigin().getJ()) * d_inv.getJ();
    double ty2 = (maximum.getJ() - ray.getOrigin().getJ()) * d_inv.getJ();

    tmin = std::max(tmin, std::min(ty1, ty2));
    tmax = std::min(tmax, std::max(ty1, ty2));

    double tz1 = (minimum.getK() - ray.getOrigin().getK()) * d_inv.getK();
    double tz2 = (maximum.getK() - ray.getOrigin().getK()) * d_inv.getK();

    tmin = std::max(tmin, std::min(tz1, tz2));
    tmax = std::min(tmax, std::max(tz1, tz2));

    return tmax >= std::max(0.0, tmin);
//    auto invD = 1.0f / ray.getDirection().getI();
//    auto t0 = (minimum.getI() - ray.getOrigin().getI()) * invD;
//    auto t1 = (maximum.getI() - ray.getOrigin().getI()) * invD;
//    if (invD < 0.0f)
//        std::swap(t0, t1);
//
//    if (t1 <= t0)
//        return false;
//
//
//    invD = 1.0f / ray.getDirection().getJ();
//    t0 = (minimum.getJ() - ray.getOrigin().getJ()) * invD;
//    t1 = (maximum.getJ() - ray.getOrigin().getJ()) * invD;
//    if (invD < 0.0f)
//        std::swap(t0, t1);
//
//    if (t1 <= t0)
//        return false;
//
//
//    invD = 1.0f / ray.getDirection().getK();
//    t0 = (minimum.getK() - ray.getOrigin().getK()) * invD;
//    t1 = (maximum.getK() - ray.getOrigin().getK()) * invD;
//    if (invD < 0.0f)
//        std::swap(t0, t1);
//
//    if (t1 <= t0)
//        return false;
//
//    return t0;
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
    os << "AABB{" << aabb.minimum << ", size " << aabb.maximum - aabb.minimum << "}";
    return os;
}
