//
// Created by kaappo on 11.9.2021.
//

#include "Ray.h"

Ray::Ray(const Vector3 &origin, const Vector3& direction) : origin(origin), direction(direction) {}

const Vector3 &Ray::getOrigin() const {
    return origin;
}

const Vector3 &Ray::getDirection() const {
    return direction;
}

Vector3 Ray::apply(double lambda) const {
    return origin + direction * lambda;
}
