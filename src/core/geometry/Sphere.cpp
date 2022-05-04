//

#include "Sphere.h"
#include <cmath>
#include <utility>
#include <iostream>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/random.hpp>
#include "../common/mytypes.h"

//
// Created by kaappo on 14.9.2021.
Sphere::Sphere (glm::vec3 center, float radius, const Material* material) : center{std::move(center)}, radius{radius}, material(material) {}

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

std::ostream& Sphere::print (std::ostream& os) const {
    return os << "Sphere{radius: " << radius << ", center: " << center << "}";
}

glm::vec3 Sphere::getNormalAt (const glm::vec3& position) const {
    return glm::normalize(position - center);
}


glm::vec3 refractAlt (const glm::vec3& uv, const glm::vec3& n, float etai_over_etat) {
    float cos_theta = glm::min(dot(-uv, n), 1.0f);
    glm::vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    glm::vec3 r_out_parallel = (float) -glm::sqrt(glm::abs(1.0 - glm::length2(r_out_perp))) * n;
    return r_out_perp + r_out_parallel;
}



glm::vec3 Sphere::refract (const glm::vec3& position, const glm::vec3& direction, std::stack<float>& opticalDensities) const {
    return direction;
//    glm::vec3 normal = getNormalAt(position);
//
//    float n = opticalDensities.top() / getMaterial()->opticalDensity;
////    float n = ;
//    opticalDensities.push(getMaterial()->opticalDensity);
//
//    float cosI = -glm::dot(normal, glm::normalize(direction));
//    if (cosI < 0) {
////        n = 1 / n;
////        cosI *= -1;
//        normal = -normal;
////        opticalDensities.pop();
//        n = 1 / n;
////        opticalDensities.pop();
//    } else {
//    }
//
//    float sinT2 = (1.0 - glm::pow(cosI, 2));
////    if (sinT2 * glm::pow(n, 2) > 1.0 or reflectance(cosI, n) > glm::linearRand(0, 1)) {
//    if (sinT2 * glm::pow(n, 2) > 1.0) {
////        std::cout << "Reflecting " << glm::to_string(direction) << glm::to_string(normal) << std::endl;
//        return glm::reflect(direction, normal);
//    } else {
//        const glm::vec3& vec = glm::refract(direction, normal, n);
//        return vec;
////        return refractAlt(direction, normal, n);
//    }
//        return glm::refract(direction, normal, n);
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
    return material;
}
