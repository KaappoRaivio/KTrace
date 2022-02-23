//
// Created by kaappo on 28.1.2022.
//

#include <glm/gtx/string_cast.hpp>
#include "AABB.h"
#include "Surface.h"

double AABB::getIntersectionDistance (const Ray& ray) const {
    return intersects(ray);
}

double AABB::intersects (const Ray& ray) const {
    const auto& d_inv = ray.getInverseDirection();

    double tx1 = (minimum.x - ray.getOrigin().x) * d_inv.x;
    double tx2 = (maximum.x - ray.getOrigin().x) * d_inv.x;

    double tmin = std::min(tx1, tx2);
    double tmax = std::max(tx1, tx2);

    double ty1 = (minimum.y - ray.getOrigin().y) * d_inv.y;
    double ty2 = (maximum.y - ray.getOrigin().y) * d_inv.y;

    tmin = std::max(tmin, std::min(ty1, ty2));
    tmax = std::min(tmax, std::max(ty1, ty2));

    double tz1 = (minimum.z - ray.getOrigin().z) * d_inv.z;
    double tz2 = (maximum.z - ray.getOrigin().z) * d_inv.z;

    tmin = std::max(tmin, std::min(tz1, tz2));
    tmax = std::min(tmax, std::max(tz1, tz2));

    return tmax >= std::max(0.0, tmin);
}

AABB::AABB (const glm::vec3& minimum, const glm::vec3& maximum) : minimum(minimum), maximum(maximum) {}

bool AABB::operator== (const AABB& rhs) const {
    return minimum == rhs.minimum &&
           maximum == rhs.maximum;
}

bool AABB::operator!= (const AABB& rhs) const {
    return !(rhs == *this);
}

AABB AABB::expand (const AABB& aabb) {
    glm::vec3 newMinimum{std::min(minimum.x, aabb.minimum.x),
                         std::min(minimum.y, aabb.minimum.y),
                         std::min(minimum.z, aabb.minimum.z)};

    glm::vec3 newMaximum{std::max(maximum.x, aabb.maximum.x),
                         std::max(maximum.y, aabb.maximum.y),
                         std::max(maximum.z, aabb.maximum.z)};

    return {newMinimum, newMaximum};

}

glm::vec3 AABB::getMinimum () const {
    return minimum;
}

glm::vec3 AABB::getMaximum () const {
    return maximum;
}

std::ostream& operator<< (std::ostream& os, const AABB& aabb) {
    os << "AABB{" << glm::to_string(aabb.minimum) << ", size " << glm::to_string(aabb.maximum - aabb.minimum) << "}";
    return os;
}
