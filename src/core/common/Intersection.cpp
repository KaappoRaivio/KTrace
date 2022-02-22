//
// Created by kaappo on 22.2.2022.
//
#include "Intersection.h"

#include "../geometry/Surface.h"

std::ostream& operator<< (std::ostream& os, const Intersection& intersection) {
    return os << "Intersection{distance: " << intersection.distance << " position: " << glm::to_string(intersection.position) << " hitSurface: " << *(intersection.hitSurface) << " material: " << *intersection.material << " ray: " << intersection.ray << "}";
}

