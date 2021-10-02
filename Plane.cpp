//
// Created by kaappo on 11.9.2021.
//
#include <cmath>
#include <utility>
#include <optional>

#include "Plane.h"

extern const double PRECISION_LIMIT;

Plane::Plane (MyVector3 normal, double intersect) : normal{std::move(normal)}, intersect{intersect} {}

double Plane::get_intersection_distance (const Ray& ray) const {
    if (normal * ray.getDirection() == 0) {
        return 0.0;
    } else {
        return -(normal * ray.getOrigin() + intersect) / (normal * ray.getDirection());
    }
}

Plane Plane::from_three_points (const MyVector3& t1, const MyVector3& t2, const MyVector3& t3) {
    auto normal = (t1 - t2).cross(t1 - t3);
    auto intersect = -normal * t1;

    return {normal, intersect};
}

bool Plane::includes (const MyVector3& vector) const {
    return std::abs(normal * vector + intersect) <= PRECISION_LIMIT;
}

const MyVector3& Plane::getNormal () const {
    return normal;
}

double Plane::getIntersect () const {
    return intersect;
}


MyVector3 Plane::get_normal_at (const MyVector3& position) const {
    return normal;
}

MyVector3 Plane::get_uv_at (const MyVector3& position) const {
    const MyVector3& tangent = normal.cross(MyVector3::UP) || normal.cross(MyVector3::OUT) || normal.cross(MyVector3::SIDE);
    const MyVector3& bitangent = normal.cross(tangent);

    const MyVector3& components = position.inTermsOfComponents(tangent, bitangent, normal);

    return components;
}


