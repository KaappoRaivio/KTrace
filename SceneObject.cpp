//
// Created by kaappo on 12.9.2021.
//

#include "SceneObject.h"

#include <utility>

SceneObject::SceneObject(Surface* surface, Material material) : surface(surface), material(material) {}

const Surface* SceneObject::getSurface() const {
    return surface;
}

const Material &SceneObject::getMaterial() const {
    return material;
}

std::optional<Intersection> SceneObject::get_intersection(const Ray &ray) const {
    auto distance = getSurface()->get_intersection_distance(ray);

//    std::cout << "Ray: " << ray << std::endl;
    if (distance == 0 || distance < 0.001) {
//        std::cout << distance << std::endl;
        return std::nullopt;
    } else {
//        std::cout << distance << ", " << ray.apply(distance) << ", " << ray << std::endl;
        return Intersection{distance, ray.apply(distance), *this, ray};
    }
}
