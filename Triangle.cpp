//
// Created by kaappo on 11.9.2021.
//

#include "Triangle.h"

Triangle::Triangle (const MyVector3& t1, const MyVector3& t2, const MyVector3& t3) : t1{t1}, t2{t2}, t3{t3}, plane{Plane::from_three_points(t1, t2, t3)} {}

Triangle::Triangle (std::initializer_list<MyVector3> list) : Triangle(list.begin()[0], list.begin()[1], list.begin()[2]) {}


double Triangle::get_intersection_distance (const Ray& ray) const {
//    std::cout << "Raydestroyed: " << ray << std::endl;
    auto possible_intersection = plane.get_intersection_distance(ray);
    if (possible_intersection == 0) {
//        std::cout << "Early return" << std::endl;
        return 0.0;
    }

    auto position = ray.apply(possible_intersection);
    if (includes(position)) {
        return possible_intersection;
    } else {
        return 0.0;
    }
}

bool Triangle::includes (const MyVector3& vector) const {
    return plane.includes(vector) && check_bounds(vector);
}

bool Triangle::check_bounds (const MyVector3& vector) const {
//        const MyVector3& v1 = t2 - t3;
//    const MyVector3& v2 = t1 - t3;
//    const MyVector3& v3 = t2 - t1;
//
//    const MyVector3& b1 = v1.cross(v2);
//    const MyVector3& b2 = v2.cross(v1);
//    const MyVector3& b3 = v2.cross(v3);
//
//
//    auto a = v1.cross(vector - t3);
//    auto c = a.dot(b1);
//    if (c < 0) return false;
//
//    a = v2.cross(vector - t3);
//    c = a.dot(b2);
//    if (c < 0) return false;
//
//    a = v3.cross(vector - t1);
//    c = a.dot(b3);
//    if (c < 0) return false;
//
//    return true;


    const MyVector3& P = vector;

// Compute vectors
    const MyVector3& v0 = t3 - t1;
    const MyVector3& v1 = t2 - t1;
    const MyVector3& v2 = P - t1;

// Compute dot products
    double dot00 = v0.squared();
    double dot01 = v0.dot(v1);
    double dot02 = v0.dot(v2);
    double dot11 = v1.squared();
    double dot12 = v1.dot(v2);

// Compute barycentric coordinates
    double invDenom = 1.0 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

// Check if point is in triangle
    return (u >= 0) && (v >= 0) && (u + v < 1);


}

MyVector3 Triangle::get_normal_at (const MyVector3& position) const {
    return plane.getNormal();
}

MyVector3 Triangle::get_uv_at (const MyVector3& position) const {
    const MyVector3& tangent = t3 - t1;
    const MyVector3& normal = get_normal_at(position);

    const MyVector3& width = tangent;
    const MyVector3& height = t2 - t1 - width * ((width * t2 - width * t1) / width.squared());

    const MyVector3& local_position = position - t1;
    const MyVector3& uv = local_position.inTermsOfComponents(width, height, normal.normalize());
    return uv;


    const MyVector3& P = position;

// Compute vectors
    const MyVector3& v0 = t3 - t1;
    const MyVector3& v1 = t2 - t1;
    const MyVector3& v2 = P - t1;

// Compute dot products
    double dot00 = v0.squared();
    double dot01 = v0.dot(v1);
    double dot02 = v0.dot(v2);
    double dot11 = v1.squared();
    double dot12 = v1.dot(v2);

// Compute barycentric coordinates
    double invDenom = 1.0 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return {u, v, 0};

}

