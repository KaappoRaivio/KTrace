//
// Created by kaappo on 11.9.2021.
//
#include <cmath>
#include <utility>
#include <optional>

#include "Plane.h"
#include "../common/mytypes.h"

Plane::Plane (MyVector3 normal, double intersect, const Material* material) : normal{std::move(normal)}, intersect{intersect}, material(material) {}

double Plane::getIntersectionDistance (const Ray& ray, Surface*& hitSurface, const Material*& hitMaterial) {
    hitMaterial = getMaterial();

    if (normal * ray.getDirection() == 0) {
        return 0.0;
    } else {
        hitSurface = this;
        hitMaterial = getMaterial();
//        std::cout << "mossi" << std::endl;
        return -(normal * ray.getOrigin() + intersect) / (normal * ray.getDirection());
    }
}

Plane Plane::from_three_points (const MyVector3& t1, const MyVector3& t2, const MyVector3& t3, const Material* material) {
    auto normal = (t1 - t2).cross(t1 - t3);
    auto intersect = -normal * t1;

    return {normal, intersect, material};
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


MyVector3 Plane::getNormalAt (const MyVector3& position) const {
    return normal;
}

MyVector3 Plane::getUVAt (const MyVector3& position) const {
    const MyVector3& tangent = normal.cross(MyVector3::UP) || normal.cross(MyVector3::OUT) || normal.cross(MyVector3::SIDE);
    const MyVector3& bitangent = normal.cross(tangent);

    const MyVector3& components = position.inTermsOfComponents(tangent, bitangent, normal);

    return components;
}

AABB Plane::getBoundingBox () const {
    return AABBs::INVALID;
}

const Material* Plane::getMaterial () const {
    return material;
}

