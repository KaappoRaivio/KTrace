//
// Created by kaappo on 11.9.2021.
//
#include <cmath>
#include <utility>
#include <optional>

#include "Plane.h"

#ifndef PRECISION_LIMIT
#define PRECISION_LIMIT 0.001
#endif

Plane::Plane(const Vector3& normal, double intersect) : normal{normal}, intersect{intersect} {}

double Plane::get_intersection_distance(const Ray &ray) const {
    if (normal * ray.getDirection() == 0) {
        return 0.0;
    } else {
        return -(normal * ray.getOrigin() + intersect) / (normal * ray.getDirection());
    }
}

Plane Plane::from_three_points(const Vector3 &t1, const Vector3 &t2, const Vector3 &t3) {
    auto normal = (t1 - t2).cross(t1 - t3);
    auto intersect = -normal * t1;

    return {normal, intersect};
}

bool Plane::includes(const Vector3 &vector) const {
    return std::abs(normal * vector + intersect) <= 0.1;
}

const Vector3 &Plane::getNormal() const {
    return normal;
}

double Plane::getIntersect() const {
    return intersect;
}

double Plane::get_intersection(const Ray &ray) const {
    return get_intersection_distance(ray);
}

Vector3 Plane::get_normal_at(const Vector3 &position) const {
    return normal;
}


