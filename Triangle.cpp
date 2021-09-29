//
// Created by kaappo on 11.9.2021.
//

#include "Triangle.h"

Triangle::Triangle (const Vector3& t1, const Vector3& t2, const Vector3& t3) : t1{t1}, t2{t2}, t3{t3}, plane{Plane::from_three_points(t1, t2, t3)} {}

Triangle::Triangle (std::initializer_list<Vector3> list) : Triangle(list.begin()[0], list.begin()[1], list.begin()[2]) {}


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

bool Triangle::includes (const Vector3& vector) const {
    return plane.includes(vector) && check_bounds(vector);
}

bool Triangle::check_bounds (const Vector3& vector) const {
//        const Vector3& v1 = t2 - t3;
//    const Vector3& v2 = t1 - t3;
//    const Vector3& v3 = t2 - t1;
//
//    const Vector3& b1 = v1.cross(v2);
//    const Vector3& b2 = v2.cross(v1);
//    const Vector3& b3 = v2.cross(v3);
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


    const Vector3& P = vector;

// Compute vectors
    const Vector3& v0 = t3 - t1;
    const Vector3& v1 = t2 - t1;
    const Vector3& v2 = P - t1;

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

Vector3 Triangle::get_normal_at (const Vector3& position) const {
    return plane.getNormal();
}

Vector3 Triangle::get_uv_at (const Vector3& position) const {
    const Vector3& tangent = t3 - t1;
    const Vector3& normal = get_normal_at(position);

    const Vector3& width = tangent;
    const Vector3& height = t2 - t1 - width * ((width * t2 - width * t1) / width.squared());

    const Vector3& local_position = position - t1;
    const Vector3& uv = local_position.inTermsOfComponents(width, height, normal.normalize());
//    std::cout << uv << std::endl;
    return uv;

//    return {0.5, 0.8, 0};
}

