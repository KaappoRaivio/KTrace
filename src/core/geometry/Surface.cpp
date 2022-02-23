//
// Created by kaappo on 11.9.2021.
//

#include "Surface.h"
#include "../common/mytypes.h"


bool Surface::getIntersection (const Ray& ray, Intersection& out) {
//    const Material& material = getMaterial();
    Intersection intersection;
    if (getIntersectionDistance(ray, intersection)) {
        intersection.ray = ray;
        intersection.position = ray.apply(intersection.distance);
//        return intersection;
        out = intersection;
        return true;
    } else {
//        return std::nullopt;
        return false;
    }
//    std::cout <<" moi" << (hitSurface == nullptr) << std::endl;


////    std::cout << "Ray: " << ray << std::endl;
//    if (distance == 0 || distance < PRECISION_LIMIT) {
////        std::cout << distance << std::endl;
//        return std::nullopt;
//    } else {
////        std::cout << distance << ", " << ray.apply(distance) << ", " << ray << std::endl;
////        return Intersection{distance, ray.apply(distance), *this, ray};
//        if (DEBUG) {
////            std::cout <<" moi" << *hitMaterial << std::endl;
////            std::cout <<" moi" << hitMaterial->getAlbedoAt({0.5, 0.5, 0}) << std::endl;
//        }
//
//        return Intersection{distance, ray.apply(distance), hitSurface, hitMaterial, ray};
//    }
}

glm::vec3 Surface::refract (const glm::vec3& position, const glm::vec3& direction, std::stack<float>& opticalDensities) const {
    return direction;
}

std::ostream& operator<< (std::ostream& os, const Surface& surface) {
    surface.print(os);
    return os;
}

glm::vec3 Surface::getBumpedNormalAt (const glm::vec3& position) const {
    return getMaterial()->getBumpAt(getUVAt(position), getNormalAt(position));
}

std::ostream& Surface::print (std::ostream& os) const {
    os << "Surface{}" << std::endl;
    return os;
}
