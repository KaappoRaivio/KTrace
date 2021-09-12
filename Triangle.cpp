//
// Created by kaappo on 11.9.2021.
//

#include "Triangle.h"

Triangle::Triangle(const Vector3 &t1, const Vector3 &t2, const Vector3 &t3) : t1{t1}, t2{t2}, t3{t3}, plane{Plane::from_three_points(t1, t2, t3)} {}

Triangle::Triangle(std::initializer_list<Vector3> list) : Triangle(list.begin()[0], list.begin()[1], list.begin()[2]) {}


double Triangle::get_intersection_distance(const Ray &ray) const {
    double intersection_distance = plane.get_intersection_distance(ray);
    if (intersection_distance == 0) {
        std::cout << "Early return" << std::endl;
        return 0;
    }

    auto position = ray.apply(intersection_distance);
    if (includes(position)) {
        return intersection_distance;
    } else {
        return 0;
    }
}

bool Triangle::includes(const Vector3 &vector) const {
    return plane.includes(vector) && check_bounds(vector);
}

bool Triangle::check_bounds(const Vector3 &vector) const {
    const Vector3 &v1 = t2 - t3;
    const Vector3 &v2 = t1 - t3;
    const Vector3 &v3 = t2 - t1;

    const Vector3 &b1 = v1.cross(v2);
    const Vector3 &b2 = v2.cross(v1);
    const Vector3 &b3 = v2.cross(v3);


    auto a = v1.cross(vector - t3);
    auto c = a * b1;
    if (c < 0) return false;

    a = v2.cross(vector - t3);
    c = a * b2;
    if (c < 0) return false;

    a = v3.cross(vector - t1);
    c = a * b3;
    if (c < 0) return false;

    return true;


//    a = (self.t2 - self.t3) @ (vector - self.t3)
//    c = a * ((self.t2 - self.t3) @ (self.t1 - self.t3))
//
//    if c < 0: return False
//
//    a = (self.t1 - self.t3) @ (vector - self.t3)
//    c = a * ((self.t1 - self.t3) @ (self.t2 - self.t3))
//
//    if c < 0: return False
//
//    a = (self.t2 - self.t1) @ (vector - self.t1)
//    c = a * ((self.t2 - self.t1) @ (-self.t1 - self.t3))
//
//    if c < 0: return False
//
//    return True
}


