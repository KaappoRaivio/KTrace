////
//// Created by kaappo on 12.9.2021.
////
//
//#include "SingleSceneObject.h"
//
//#include <utility>
//
//SingleSceneObject::SingleSceneObject (Surface* surface, Material material) : surface{surface}, material(material) {}
//
//Surface* SingleSceneObject::getSurface () const {
//    return surface;
//}
//
//const Material& SingleSceneObject::getMaterial () const {
//    return material;
//}
//
//std::optional<Intersection> SingleSceneObject::getIntersection (const Ray& ray) const {
//    Surface* hitSurface = surface;
//    auto distance = getSurface()->getIntersectionDistance(ray, hitSurface, nullptr);
//
////    std::cout << "Ray: " << ray << std::endl;
//    if (distance == 0 || distance < 0.001) {
////        std::cout << distance << std::endl;
//        return std::nullopt;
//    } else {
////        std::cout << distance << ", " << ray.apply(distance) << ", " << ray << std::endl;
////        return Intersection{distance, ray.apply(distance), *this, ray};
//        return Intersection{distance, ray.apply(distance), hitSurface, material, ray};
//    }
//}
//
//std::ostream& operator<< (std::ostream& os, const SingleSceneObject& object) {
//    os << "Surface lol";
//    return os;
//}
