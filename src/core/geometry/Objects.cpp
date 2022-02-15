//
// Created by kaappo on 28.1.2022.
//

#include "Objects.h"
#include "../common/mytypes.h"

MyVector3 Objects::getNormalAt (const MyVector3& position) const {
    throw std::runtime_error("Normal generation not implemented!");
}

MyVector3 Objects::getUVAt (const MyVector3& position) const {
    throw std::runtime_error("UV mapping not implemented!");
}

const Material* Objects::getMaterial () const {
    return surfaces[0]->getMaterial();
}

Objects::Objects (std::vector<std::unique_ptr<Surface>> surfaces) : surfaces{std::move(surfaces)} {

}

double Objects::getIntersectionDistance (const Ray& ray, const Surface*& hitSurface, const Material*& hitMaterial) const {
    const Surface* tempHitSurface = nullptr;
    const Material* tempHitMaterial = nullptr;

    double closest_hit = 1e9;

    for (const auto& surface : surfaces) {
        double candidate = surface->getIntersectionDistance(ray, tempHitSurface, tempHitMaterial);

        if (std::abs(candidate) > PRECISION_LIMIT && candidate < closest_hit) {
            closest_hit = candidate;
            hitSurface = tempHitSurface;
            hitMaterial = tempHitMaterial;
//            if (hitSurface == nullptr) {
//                std::cout << "Problem!" << std::endl;
//            } else {
//                std::cout << *hitSurface << std::endl;
//
//            }
        }
    }


    return closest_hit == 1e9 ? 0 : closest_hit;
}

AABB Objects::getBoundingBox () const {
    if (surfaces.empty()) return AABBs::INVALID;

    AABB result = AABBs::INVALID;
    bool firstBox = true;
//
    for (const auto& surface : surfaces) {
        const AABB& temp = surface->getBoundingBox();
        if (temp == AABBs::INVALID) return AABBs::INVALID;
        if (firstBox) result = temp;
        firstBox = false;

        result = result.expand(temp);
    }

    return result;
}

