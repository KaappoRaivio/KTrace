//

#include "Sphere.h"
#include <cmath>
#include <utility>
#include <iostream>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "../common/mytypes.h"

//
// Created by kaappo on 14.9.2021.
Sphere::Sphere (glm::vec3 center, float radius, Material material) : center{std::move(center)}, radius{radius}, material(material) {}

float Sphere::getIntersectionDistance (const Ray& ray, const Surface*& hitSurface, const Material*& hitMaterial) const {
//    if (includes(ray.getOrigin())) {
//        return 0.0;
//    }

    const auto& d = ray.getDirection();
    const auto& C = ray.getOrigin();
    const auto& r = radius;
    const auto& P = center;

    const auto discriminant = std::pow(glm::dot(d, C - P), 2) - (glm::length2(C - P) - std::pow(r, 2));
    if (discriminant < 0) {
        return 0.0;
    }

    const auto base = -glm::dot(d, (C - P));
    hitSurface = this;
    hitMaterial = getMaterial();
    if (discriminant == 0) {
        if (base < PRECISION_LIMIT) return 0.0;
        else return base;
    } else {
        const float root1 = base - std::sqrt(discriminant);
        const float root2 = base + std::sqrt(discriminant);

        if (root1 < PRECISION_LIMIT) return root2;
        else if (root2 < PRECISION_LIMIT) return 0.0;
        else return std::min(root1, root2);
    }
}

glm::vec3 Sphere::getNormalAt (const glm::vec3& position) const {
    return glm::normalize(position - center);
}

glm::vec3 Sphere::refract (const glm::vec3& position, const glm::vec3& direction, std::stack<float>& opticalDensities) const {
    glm::vec3 normal = getNormalAt(position);
    bool inwards = glm::dot(normal, direction) < 0;
//

    float n = opticalDensities.top() / getMaterial()->opticalDensity;
    opticalDensities.push(getMaterial()->opticalDensity);

//    float n;
//    if (false) {
//    if (inwards) {
//        float n = 1.33;
//    } else {
//        n = 1 / 1.33;
//    }

//    float n1;
//    float n2;
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
//    float r = n1 / n2;
//    float normal = n1 / n2;
//    const float cosI = -dot(normal, direction);
//    return glm::refract(direction, normal, n);
//    float eta = n;
//    float k = 1.0 - eta * eta * (1.0 - glm::dot(normal, direction) * dot(normal, direction));
//    if (k < 0.0)
//        return glm::reflect(direction, normal);
//    else {
////        std::cout << "moi" << std::endl;
////        std::cout << glm::to_string(eta * direction - (eta * glm::dot(normal, direction) + std::sqrt(k)) * normal) << std::endl;
//        return eta * direction - (eta * glm::dot(normal, direction) + std::sqrt(k)) * normal;
//    }


    float cosI = -glm::dot(normal, glm::normalize(direction));
    if (cosI < 0) {
        cosI *= -1;
        n = 1 / n;
//        normal = -normal;
//        opticalDensities.pop();
//        opticalDensities.pop();
    }
//    float cosI = std::abs(-normal * direction.normalize());
    float sinT2 = n * n * (1.0 - cosI * cosI);
    if (sinT2 > 1.0) {
//        std::cout << "mosi" << std::endl;
        return glm::reflect(direction, normal);
    }
    if (sinT2 < 0)
        std::cout << sinT2 << std::endl;

//    return glm::refract(direction, normal, n);

    float cosT = sqrt(1.0 - sinT2);
    return direction * n + normal * (n * cosI - cosT);
}

bool Sphere::includes (const glm::vec3& point) const {
//    return glm::intersectLineSphere()
    return std::abs(glm::length2(center - point) - std::pow(radius, 2)) < PRECISION_LIMIT;
}

glm::vec3 Sphere::getUVAt (const glm::vec3& position) const {
    const auto& d = glm::normalize(center - position);

    float u = 0.5 - glm::atan(d.y, d.x) / (2 * M_PI);
    float v = 0.5 + glm::asin(d.z) / M_PI;

    return {u + 0.2, v, 0};
}

AABB Sphere::getBoundingBox () const {
    auto corner = glm::vec3{radius, radius, radius};
    return AABB{center - corner, center + corner};
}

const Material* Sphere::getMaterial () const {
    return &material;
}
