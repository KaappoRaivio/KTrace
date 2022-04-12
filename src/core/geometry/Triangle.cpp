//
// Created by kaappo on 11.9.2021.
//

#include "Triangle.h"
#include <glm/ext.hpp>
#include "glm/gtx/string_cast.hpp"
#include "../../Config.h"
#include <iostream>


//glm::vec3 getUVWithoutMapping (const glm::vec3& P) const;

Triangle::Triangle (const glm::vec3& t1, const glm::vec3& t2, const glm::vec3& t3, const Material* material, const glm::vec3& texture1, const glm::vec3& texture2, const glm::vec3& texture3, const glm::vec3& normal1, const glm::vec3& normal2, const glm::vec3& normal3) : t1{t1}, t2{t2}, t3{t3}, tu{texture1}, tv{texture2}, tw{texture3}, n1{normal1}, n2{normal2}, n3{normal3}, plane{Plane::from_three_points(t1, t2, t3, material)}, v0{t2 - t1}, v1{t3 - t1} {
    d00 = glm::dot(v0, v0);
    d01 = glm::dot(v0 , v1);
    d11 = glm::dot(v1, v1);
    invDenom = 1.0 / (d00 * d11 - d01 * d01);

//    if (glm::dot(plane.getNormal(), n1) < 0 and glm::dot(plane.getNormal(), n2) < 0 and glm::dot(plane.getNormal(), n3) < 0) plane

//    if (glm::dot(n1, plane.getNormal()) < 0) n1 *= -1;
//    if (glm::dot(n2, plane.getNormal()) < 0) n2 *= -1;
//    if (glm::dot(n3, plane.getNormal()) < 0) n3 *= -1;

    if (glm::length(normal1) == 0 or glm::length(normal2) == 0 or glm::length(normal3) == 0) {
        n1 = n2 = n3 = plane.getNormal();
    }

}

Triangle::Triangle (const glm::vec3& t1, const glm::vec3& t2, const glm::vec3& t3, const Material* material, const glm::vec3& texture1, const glm::vec3& texture2, const glm::vec3& texture3)
        : Triangle(t1, t2, t3, material, texture1, texture2, texture3, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}) {

//    v0 = p2 - p1;
//    v1 = p3 - p1;
//    d00 = glm::dot(v0, v0);
//    d01 = glm::dot(v0 , v1);
//    d11 = glm::dot(v1, v1);
//    invDenom = 1.0 / (d00 * d11 - d01 * d01);
}

std::ostream& Triangle::print (std::ostream& os) const {
    return os << "Triangle{" << glm::to_string(t1) << ", " << glm::to_string(t2) << ", " << glm::to_string(t3) << "}";
}


Triangle::Triangle (const glm::vec3& t1, const glm::vec3& t2, const glm::vec3& t3, const Material* material) : Triangle{t1, t2, t3, material, {0, 0, 0}, {1, 0, 0}, {0, 1, 0}} {

}

bool Triangle::getIntersectionDistance (const Ray& ray, Intersection& out) const {
//    std::cout << "Raydestroyed: " << glm::to_string(ra)y << std::endl;
    Intersection temp;
    bool intersects = plane.getIntersectionDistance(ray, temp);
    if constexpr (Config::BACKFACE_CULLING) {
        if (not intersects or -glm::dot(ray.getDirection(), plane.getNormal()) < 0) {
    //        std::cout << "Early return" << std::endl;
            return false;
        }
    } else {
        if (not intersects) return false;
    }

    auto position = ray.apply(temp.distance);
    if (includes(position)) {
        temp.hitSurface = this;
        out = temp;

        return true;
//        out = this;
//        hitMaterial = getMaterial();
//        return possible_intersection;
    } else {
        return false;
    }
}

bool Triangle::includes (const glm::vec3& vector) const {
    return plane.includes(vector) && check_bounds(vector);
}

bool Triangle::check_bounds (const glm::vec3& P) const {
    const glm::vec3& v2 = P - t1;
    float d02 = glm::dot(v0, v2);
    float d12 = glm::dot(v1, v2);

    float u = (d11 * d02 - d01 * d12) * invDenom;
    float v = (d00 * d12 - d01 * d02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);


}

glm::vec3 Triangle::getNormalAt (const glm::vec3& position) const {
//    return plane.getNormal();
//    std::cout << "moi <" << std::endl;
    const glm::vec3& uvw = getUVWithoutMapping(position);
//    std::cout << glm::to_string(uvw) << std::endl;
//    return
    return glm::normalize(n1 * uvw.x + n2 * uvw.y + n3 * uvw.z);

//
}

glm::vec3 Triangle::getUVAt (const glm::vec3& P) const {
//    glm::vec3 v2 = P - p1;
//
//    float d02 = glm::dot(v0, v2);
//    float d12 = glm::dot(v1, v2);
    glm::vec3 uvw = getUVWithoutMapping(P);


//    return tu * u + tv * v + tw * w;
    return tu * uvw.x + tv * uvw.y + tw * uvw.z;
}

glm::vec3 Triangle::getUVWithoutMapping(const glm::vec3& P) const {
    glm::vec3 v2 = P - t1;

    float d02 = glm::dot(v0, v2);
    float d12 = glm::dot(v1, v2);

    float v = (d11 * d02 - d01 * d12) * invDenom;
    float w = (d00 * d12 - d01 * d02) * invDenom;
    float u = 1.0f - v - w;

    return {u, v, w};
}

glm::vec3 Triangle::refract (const glm::vec3& position, const glm::vec3& direction, std::stack<float>& opticalDensities) const {
    return direction;
//    glm::vec3 normal = getNormalAt(position);
////    bool inwards = glm::dot(normal, direction) < 0;
////
//    float n = opticalDensities.top() / getMaterial()->opticalDensity;
//    opticalDensities.push(getMaterial()->opticalDensity);
//
//    float cosI = -glm::dot(normal, glm::normalize(direction));
//    if (cosI < 0) {
//        cosI *= -1;
//        normal = -normal;
//    }
//
//    float sinT2 = n * n * (1.0 - cosI * cosI);
//    if (sinT2 > 1.0) {
//        return glm::reflect(direction, normal);
//    }
//
//    return glm::refract(direction, normal, n);
//
//    float cosT = sqrt(1.0 - sinT2);
//    return direction * n + normal * (n * cosI - cosT);
}

std::ostream& operator<< (std::ostream& os, const Triangle& triangle) {
    os << "Triangle{" << glm::to_string(triangle.t1) << ", " << glm::to_string(triangle.t2) << ", " << glm::to_string(triangle.t3) << "}";
    return os;
}

AABB Triangle::getBoundingBox () const {
    float smallestX = std::min(t1.x, std::min(t2.x, t3.x));
    float greatestX = std::max(t1.x, std::max(t2.x, t3.x));

    float smallestY = std::min(t1.y, std::min(t2.y, t3.y));
    float greatestY = std::max(t1.y, std::max(t2.y, t3.y));

    float smallestZ = std::min(t1.z, std::min(t2.z, t3.z));
    float greatestZ = std::max(t1.z, std::max(t2.z, t3.z));

    return AABB{{smallestX, smallestY, smallestZ},
                {greatestX, greatestY, greatestZ}};
}

const Material* Triangle::getMaterial () const {
    return plane.getMaterial();
}




