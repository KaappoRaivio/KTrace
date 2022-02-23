//
// Created by kaappo on 28.1.2022.
//

#include "Objects.h"
#include "../common/mytypes.h"

glm::vec3 Objects::getNormalAt (const glm::vec3& position) const {
    throw std::runtime_error("Normal generation not implemented!");
}

glm::vec3 Objects::getUVAt (const glm::vec3& position) const {
    throw std::runtime_error("UV mapping not implemented!");
}

const Material* Objects::getMaterial () const {
    return surfaces[0]->getMaterial();
}

Objects::Objects (std::vector<std::unique_ptr<Surface>> surfaces) : surfaces{std::move(surfaces)} {

}

bool Objects::getIntersectionDistance (const Ray& ray, Intersection& out) const {
    float closest_hit = 1e9;
//    Intersection intersection;

    for (const auto& surface : surfaces) {
        Intersection tempIntersection;
        double candidate = surface->getIntersectionDistance(ray, tempIntersection);

        if (std::abs(candidate) > PRECISION_LIMIT && candidate < closest_hit) {
            closest_hit = candidate;
            out = tempIntersection;
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

