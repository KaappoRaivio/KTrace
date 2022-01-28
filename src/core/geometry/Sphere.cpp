//

#include "Sphere.h"
#include <cmath>
#include <utility>
#include "../common/mytypes.h"

//
// Created by kaappo on 14.9.2021.
Sphere::Sphere (MyVector3 center, double radius) : center{std::move(center)}, radius{radius} {}

double Sphere::get_intersection_distance (const Ray& ray) const {
//    if (includes(ray.getOrigin())) {
//        return 0.0;
//    }

    const auto& d = ray.getDirection().normalize();
    const auto& C = ray.getOrigin();
    const auto& r = radius;
    const auto& P = center;

    const auto discriminant = std::pow(d * (C - P), 2) - ((C - P).squared() - std::pow(r, 2));
    if (discriminant < 0) {
        return 0.0;
    }

    const auto base = (-d * (C - P));
    if (discriminant == 0) {
        if (base < PRECISION_LIMIT) return 0.0;
        else return base;
    } else {
        const double root1 = base - std::sqrt(discriminant);
        const double root2 = base + std::sqrt(discriminant);

        if (root1 < PRECISION_LIMIT) return root2;
        else if (root2 < PRECISION_LIMIT) return 0.0;
        else return std::min(root1, root2);
    }
}

MyVector3 Sphere::get_normal_at (const MyVector3& position) const {
    return (position - center).normalize();
}

bool Sphere::includes (const MyVector3& point) const {
    return std::abs((center - point).squared() - std::pow(radius, 2)) < PRECISION_LIMIT;
}

MyVector3 Sphere::get_uv_at (const MyVector3& position) const {
    const auto& d = (center - position).normalize();

    double u = 0.5 - d.atan2() / (2 * M_PI);
    double v = 0.5 + d.asin() / M_PI;

    return {u, v, 0};
}
