//
// Created by kaappo on 11.9.2021.
//

#include "Triangle.h"

Triangle::Triangle (const MyVector3& t1, const MyVector3& t2, const MyVector3& t3, const Material* material, const MyVector3& texture1, const MyVector3& texture2, const MyVector3& texture3)
        : t1{t1}, t2{t2}, t3{t3}, plane{Plane::from_three_points(t1, t2, t3, *material)}, tu{texture1}, tv{texture2}, tw{texture3}, v0{t2 - t1}, v1{t3 - t1} {

//    v0 = t2 - t1;
//    v1 = t3 - t1;
    d00 = v0 * v0;
    d01 = v0 * v1;
    d11 = v1 * v1;
    invDenom = 1.0 / (d00 * d11 - d01 * d01);
}

std::ostream& Triangle::print (std::ostream& os) const {
    return os << "Triangle{" << t1 << ", " << t2 << ", " << t3 << "}";
}


Triangle::Triangle (const MyVector3& t1, const MyVector3& t2, const MyVector3& t3, const Material* material) : Triangle{t1, t2, t3, material, {0, 0, 0}, {1, 0, 0}, {0, 1, 0}} {

}

//Triangle::Triangle (std::initializer_list<MyVector3> list) : Triangle(list.begin()[0], list.begin()[1], list.begin()[2]) {}


double Triangle::getIntersectionDistance (const Ray& ray, const Surface*& hitSurface, const Material*& hitMaterial) const {
//    std::cout << "Raydestroyed: " << ray << std::endl;
    auto possible_intersection = plane.getIntersectionDistance(ray, hitSurface, hitMaterial);
    if (possible_intersection == 0) {
//        std::cout << "Early return" << std::endl;
        return 0.0;
    }

    auto position = ray.apply(possible_intersection);
    if (includes(position)) {
        hitSurface = this;
        hitMaterial = getMaterial();
        return possible_intersection;
    } else {
        return 0.0;
    }
}

bool Triangle::includes (const MyVector3& vector) const {
    return plane.includes(vector) && check_bounds(vector);
}

bool Triangle::check_bounds (const MyVector3& P) const {
    const MyVector3& v2 = P - t1;
    double d02 = v0 * v2;
    double d12 = v1 * v2;

    double u = (d11 * d02 - d01 * d12) * invDenom;
    double v = (d00 * d12 - d01 * d02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);


}

MyVector3 Triangle::getNormalAt (const MyVector3& position) const {
    return plane.getNormal();
}

MyVector3 Triangle::getUVAt (const MyVector3& P) const {
    MyVector3 v2 = P - t1;

    double d02 = v0 * v2;
    double d12 = v1 * v2;

    double v = (d11 * d02 - d01 * d12) * invDenom;
    double w = (d00 * d12 - d01 * d02) * invDenom;
    double u = 1.0f - v - w;

    return tu * u + tv * v + tw * w;

}

std::ostream& operator<< (std::ostream& os, const Triangle& triangle) {
    os << "Triangle{" << triangle.t1 << ", " << triangle.t2 << ", " << triangle.t3 << "}";
    return os;
}

AABB Triangle::getBoundingBox () const {
    double smallestX = std::min(t1.getI(), std::min(t2.getI(), t3.getI()));
    double greatestX = std::max(t1.getI(), std::max(t2.getI(), t3.getI()));

    double smallestY = std::min(t1.getJ(), std::min(t2.getJ(), t3.getJ()));
    double greatestY = std::max(t1.getJ(), std::max(t2.getJ(), t3.getJ()));

    double smallestZ = std::min(t1.getK(), std::min(t2.getK(), t3.getK()));
    double greatestZ = std::max(t1.getK(), std::max(t2.getK(), t3.getK()));

    return AABB{{smallestX, smallestY, smallestZ},
                {greatestX, greatestY, greatestZ}};
}

const Material* Triangle::getMaterial () const {
    return plane.getMaterial();
}


