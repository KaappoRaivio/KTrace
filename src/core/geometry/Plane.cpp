//
// Created by kaappo on 11.9.2021.
//
#include <cmath>
#include <utility>
#include <optional>

#include "Plane.h"
#include "../common/mytypes.h"
#include "../common/MyVector3.h"

Plane::Plane (glm::vec3 normal, double intersect, Material material) : normal{std::move(glm::normalize(normal))}, intersect{intersect}, material(material) {}

bool Plane::getIntersectionDistance (const Ray& ray, Intersection& out) const {
//    hitMaterial = getMaterial();

    if (glm::dot(normal, ray.getDirection()) == 0) {
        return false;
    }
    float distance = -(glm::dot(normal, ray.getOrigin()) + intersect) / glm::dot(normal, ray.getDirection());

    if (distance < PRECISION_LIMIT) return false;

    out.material = &material;
    out.hitSurface = this;
    out.distance = distance;
//        hitMaterial = getMaterial();
//        std::cout << "mossi" << std::endl;
//        return -(glm::dot(normal, ray.getOrigin()) + intersect) / glm::dot(normal, ray.getDirection());
    return true;

}

Plane Plane::from_three_points (const glm::vec3& t1, const glm::vec3& t2, const glm::vec3& t3, Material material) {
    glm::vec3 normal = glm::normalize(glm::cross((t1 - t2), (t1 - t3)));
    float intersect = -glm::dot(normal, t1);

    return {normal, intersect, material};
}

bool Plane::includes (const glm::vec3& vector) const {
    return std::abs(glm::dot(normal, vector) + intersect) <= PRECISION_LIMIT;
}

std::ostream& Plane::print (std::ostream& os) const {
    return os << "Plane{normal: " << glm::to_string(normal) << ", intersect: " << intersect << "}";
}

const glm::vec3& Plane::getNormal () const {
    return normal;
}

double Plane::getIntersect () const {
    return intersect;
}


glm::vec3 Plane::getNormalAt (const glm::vec3& position) const {
//    std::cout << "moiaasd " << glm::to_string(normal) << std::endl;
    return normal;
}

glm::vec3 Plane::getUVAt (const glm::vec3& position) const {
//    const glm::vec3& tangent = normal.cross(glm::vec3s::UP) || normal.cross(glm::vec3s::OUT) || normal.cross(glm::vec3s::SIDE);



    const glm::vec3& tangent = std::abs(glm::dot(normal, {0, 0, 1})) != 1 ? glm::cross(normal, {0, 0, 1})
                                                                : std::abs(glm::dot(normal, {0, 1, 0})) != 1 ? glm::cross(normal, {0, 1, 0})
                                                                                                   : glm::cross(normal, {1, 0, 0})/*|| glm::cross(normal, {0, 1, 0}) || glm::cross(normal, {1, 0, 0})*/;
    const glm::vec3& bitangent = glm::cross(normal, tangent);

    float scale = 20.0f;
    const glm::vec3& components = VectorOperations::changeComponents(position, -tangent * scale, bitangent * scale, scale * normal);

    return components + glm::vec3{0.5f, 0.f, 0};
}

AABB Plane::getBoundingBox () const {
    return AABBs::INVALID;
}

const Material* Plane::getMaterial () const {
    return &material;
}


