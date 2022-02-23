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

bool Sphere::getIntersectionDistance (const Ray& ray, Intersection& out) const {
//    if (includes(ray.getOrigin())) {
//        return 0.0;
//    }

    const auto& d = ray.getDirection();
    const auto& C = ray.getOrigin();
    const auto& r = radius;
    const auto& P = center;

    const auto discriminant = std::pow(glm::dot(d, C - P), 2) - (glm::length2(C - P) - std::pow(r, 2));
    if (discriminant < 0) {
        return false;
    }

    const auto base = -glm::dot(d, (C - P));



//    out = this;
//    hitMaterial = getMaterial();
    if (discriminant == 0) {
        if (base < PRECISION_LIMIT) return false;
        else {
            out.hitSurface = this;
            out.material = getMaterial();
            out.distance = base;
            return true;
        }
    } else {
        const float root1 = base - std::sqrt(discriminant);
        const float root2 = base + std::sqrt(discriminant);

        if (root1 < PRECISION_LIMIT and root2 < PRECISION_LIMIT) {
            return false;
        } else {
            out.hitSurface = this;
            out.material = getMaterial();
            if (root1 < PRECISION_LIMIT) out.distance = root2;
            else out.distance = std::min(root1, root2);

            return true;
        }


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

    float n = opticalDensities.top() / getMaterial()->opticalDensity;
    opticalDensities.push(getMaterial()->opticalDensity);

    float cosI = -glm::dot(normal, glm::normalize(direction));
    if (cosI < 0) {
        cosI *= -1;
        normal = -normal;
        opticalDensities.pop();
        opticalDensities.pop();
    }

    float sinT2 = n * n * (1.0 - cosI * cosI);
    if (sinT2 > 1.0) {
        return glm::reflect(direction, normal);
    }
    return glm::refract(direction, normal, n);
//    float cosT = sqrt(1.0 - sinT2);
//    return direction * n + normal * (n * cosI - cosT);
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
