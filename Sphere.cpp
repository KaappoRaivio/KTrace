//

#include "Sphere.h"
#include <cmath>
#include <utility>

extern const double PRECISION_LIMIT;

//
// Created by kaappo on 14.9.2021.
Sphere::Sphere(Vector3 center, double radius) : center{std::move(center)}, radius{radius} {}

double Sphere::get_intersection_distance(const Ray &ray) const {
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

Vector3 Sphere::get_normal_at(const Vector3 &position) const {
    return (position - center).normalize();
}

bool Sphere::includes(const Vector3 &point) const {
    return std::abs((center - point).squared() - std::pow(radius, 2)) < PRECISION_LIMIT;
}
