//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <ostream>
#include <iostream>
#include "../../../lib/Eigen/Dense"
#include <glm/glm.hpp>

class MyVector3 {
private:
//    float i, j, k;
    glm::vec3 vector;

public:
//    constexpr MyVector3 (float i, float j, float k) : vector{i, j, k} {};
    constexpr MyVector3 (double i, double j, double k) : vector{i, j, k} {}
    constexpr MyVector3 (const glm::vec3& vector) : vector{vector} {}

    MyVector3 operator+ (const MyVector3& other) const;
    MyVector3 operator|| (const MyVector3& other) const;
    MyVector3 operator- () const;
    MyVector3 operator- (const MyVector3& other) const;
    MyVector3 operator* (float other) const;
    float operator* (const MyVector3& other) const;
    MyVector3 operator/ (float other) const;
    explicit operator bool () const;
    float operator [] (int index) const;

    bool operator== (const MyVector3& rhs) const;

    bool operator!= (const MyVector3& rhs) const;

    MyVector3 rotateInsideCone (float radius) const;
    MyVector3 reflection (const MyVector3& axis) const;
    MyVector3 inTermsOfComponents (const MyVector3& i, const MyVector3& j, const MyVector3& k) const;

    MyVector3 rotate (float yaw, float pitch) const;
    MyVector3 cross (const MyVector3& other) const;
    float length () const;

    float squared () const;
    MyVector3 normalize () const;

    float atan2 () const;

    float asin () const;

    friend std::ostream& operator<< (std::ostream& os, const MyVector3& vector3);

    float getI () const;
    float getJ () const;
    float getK () const;

    static MyVector3 randomInsideUnitSphere ();


    float dot (const MyVector3& vector3) const;
};

namespace MyVector3s {
    constexpr MyVector3 UP{0, 0, 1};
    constexpr MyVector3 OUT{0, 1, 0};
    constexpr MyVector3 SIDE{1, 0, 0};
}