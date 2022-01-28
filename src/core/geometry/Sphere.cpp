//

#include "Sphere.h"
#include <cmath>
#include <utility>
#include "../common/mytypes.h"

//
// Created by kaappo on 14.9.2021.
Sphere::Sphere (MyVector3 center, double radius, const Material* material) : center{std::move(center)}, radius{radius}, material(material) {}

double Sphere::getIntersectionDistance (const Ray& ray, Surface*& hitSurface, const Material*& hitMaterial) {
//    if (includes(ray.getOrigin())) {
//        return 0.0;
//    }

    const auto& d = ray.getDirection();
    const auto& C = ray.getOrigin();
    const auto& r = radius;
    const auto& P = center;

    const auto discriminant = std::pow(d * (C - P), 2) - ((C - P).squared() - std::pow(r, 2));
    if (discriminant < 0) {
        return 0.0;
    }

    const auto base = (-d * (C - P));
    hitSurface = this;
    hitMaterial = getMaterial();
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

MyVector3 Sphere::getNormalAt (const MyVector3& position) const {
    return (position - center).normalize();
}

bool Sphere::includes (const MyVector3& point) const {
    return std::abs((center - point).squared() - std::pow(radius, 2)) < PRECISION_LIMIT;
}

MyVector3 Sphere::getUVAt (const MyVector3& position) const {
    const auto& d = (center - position).normalize();

    double u = 0.5 - d.atan2() / (2 * M_PI);
    double v = 0.5 + d.asin() / M_PI;

    return {u, v, 0};
}

AABB Sphere::getBoundingBox () const {
    auto corner = MyVector3{radius, radius, radius};
    return AABB{center - corner, center + corner};
}

const Material* Sphere::getMaterial () const {
    return material;
}