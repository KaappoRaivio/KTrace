//
// Created by kaappo on 11.9.2021.
//

#include "Surface.h"
#include "../common/mytypes.h"


std::optional<Intersection> Surface::getIntersection (const Ray& ray) {
//    const Material& material = getMaterial();
    const Surface* hitSurface = nullptr;
    const Material* hitMaterial = nullptr;
    auto distance = getIntersectionDistance(ray, hitSurface, hitMaterial);
//    std::cout <<" moi" << (hitSurface == nullptr) << std::endl;


//    std::cout << "Ray: " << ray << std::endl;
    if (distance == 0 || distance < PRECISION_LIMIT) {
//        std::cout << distance << std::endl;
        return std::nullopt;
    } else {
//        std::cout << distance << ", " << ray.apply(distance) << ", " << ray << std::endl;
//        return Intersection{distance, ray.apply(distance), *this, ray};
        if (DEBUG) {
//            std::cout <<" moi" << *hitMaterial << std::endl;
//            std::cout <<" moi" << hitMaterial->getAlbedoAt({0.5, 0.5, 0}) << std::endl;
        }

        return Intersection{distance, ray.apply(distance), hitSurface, hitMaterial, ray};
    }
}

std::ostream& operator<< (std::ostream& os, const Surface& surface) {
    surface.print(os);
    return os;
}

MyVector3 Surface::getBumpedNormalAt (const MyVector3& position) const {
    return getMaterial()->getBumpAt(getUVAt(position), getNormalAt(position));
}

std::ostream& Surface::print (std::ostream& os) const {
    os << "Surface{}" << std::endl;
    return os;
}
