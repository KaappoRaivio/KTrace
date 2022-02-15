//

#include "Sphere.h"
#include <cmath>
#include <utility>
#include "../common/mytypes.h"

//
// Created by kaappo on 14.9.2021.
Sphere::Sphere (MyVector3 center, double radius, Material material) : center{std::move(center)}, radius{radius}, material(material) {}

double Sphere::getIntersectionDistance (const Ray& ray, const Surface*& hitSurface, const Material*& hitMaterial) const {
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

MyVector3 Sphere::refract (const MyVector3& position, const MyVector3& direction, std::stack<double>& opticalDensities) const {
    const MyVector3& normal = getNormalAt(position);
    bool inwards = normal * direction < 0;
//
    double n;
    if (inwards) {
        n = 1.33;
    } else {
        n = 1 / 1.33;
    }

//    double n1;
//    double n2;
//    if (inwards) {
//        n1 = opticalDensities.top();
//        n2 = material.opticalDensity;
//        opticalDensities.push(n2);
//    } else {
//        n1 = opticalDensities.top();
//        opticalDensities.pop();
//        n2 = opticalDensities.top();
//    }
//
//
//    double r = n1 / n2;
//    double normal = n1 / n2;
//    const double cosI = -dot(normal, direction);

    double cosI = -normal * direction;
    double sinT2 = n * n * (1.0 - cosI * cosI);
    if (sinT2 > 1.0) {
        return direction.reflection(normal);
    }

    double cosT = sqrt(1.0 - sinT2);
    return direction * n + normal * (n * cosI - cosT);

//    V_refraction = r*V_incedence + (rc - sqrt(1-Math.pow(r,2)(1-Math.pow(c,2))))normal
//    where r = n1/n2 and c = -normal dot V_incedence.
//    return direction * r + normal * (r * c - std::sqrt(1 - std::pow(r, 2) * (1 - std::pow (c, 1))));
}

bool Sphere::includes (const MyVector3& point) const {
    return std::abs((center - point).squared() - std::pow(radius, 2)) < PRECISION_LIMIT;
}

MyVector3 Sphere::getUVAt (const MyVector3& position) const {
    const auto& d = (center - position).normalize();

    double u = 0.5 - d.atan2() / (2 * M_PI);
    double v = 0.5 + d.asin() / M_PI;

    return {u + 0.2, v, 0};
}

AABB Sphere::getBoundingBox () const {
    auto corner = MyVector3{radius, radius, radius};
    return AABB{center - corner, center + corner};
}

const Material* Sphere::getMaterial () const {
    return &material;
}
