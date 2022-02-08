//
// Created by kaappo on 11.9.2021.
//

#include "Ray.h"

Ray::Ray (const MyVector3& origin, const MyVector3& direction) : origin(origin), direction(direction.normalize()), inverse_direction{1.0 / direction.normalize().getI(), 1.0 / direction.normalize().getJ(), 1.0 / direction.normalize().getK()} {}

const MyVector3& Ray::getOrigin () const {
    return origin;
}

const MyVector3& Ray::getDirection () const {
    return direction;
}

MyVector3 Ray::apply (double lambda) const {
    return origin + direction * lambda;
}

std::ostream& operator<< (std::ostream& os, const Ray& ray) {
    os << "origin: " << ray.origin << " direction: " << ray.direction;
    return os;
}

const MyVector3& Ray::getInverseDirection () const {
    return inverse_direction;
}
