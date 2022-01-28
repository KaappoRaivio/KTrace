//
// Created by kaappo on 11.9.2021.
//

#include "Surface.h"
#include "../common/mytypes.h"


std::optional<Intersection> Surface::getIntersection (const Ray& ray) {
//    const Material& material = getMaterial();
    Surface* hitSurface = nullptr;
    Material hitMaterial = Materials::WHITE;
    auto distance = getIntersectionDistance(ray, hitSurface, hitMaterial);
//    std::cout <<" moi" << (hitSurface == nullptr) << std::endl;


//    std::cout << "Ray: " << ray << std::endl;
    if (distance == 0 || distance < 0.001) {
//        std::cout << distance << std::endl;
        return std::nullopt;
    } else {
//        std::cout << distance << ", " << ray.apply(distance) << ", " << ray << std::endl;
//        return Intersection{distance, ray.apply(distance), *this, ray};
//        if (DEBUG) {
//            std::cout <<" moi" << (hitSurface == nullptr) << std::endl;
//        }
        return Intersection{distance, ray.apply(distance), hitSurface, hitMaterial, ray};
    }
}

std::ostream& operator<< (std::ostream& os, const Surface& surface) {
    os << "Surface{" << *surface.getMaterial() << "}";
    return os;
}
