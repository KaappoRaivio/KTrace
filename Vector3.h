//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <ostream>
#include <iostream>
#include "lib/Eigen/Dense"

class Vector3 {
private:
    double i, j, k;

public:
    Vector3 (double i, double j, double k);

    Vector3 operator+ (const Vector3& other) const;
    Vector3 operator|| (const Vector3& other) const;
    Vector3 operator- () const;
    Vector3 operator- (const Vector3& other) const;
    Vector3 operator* (double other) const;
    double operator* (const Vector3& other) const;
    Vector3 operator/ (double other) const;
    explicit operator bool () const;

    Vector3 rotateInsideCone (double radius) const;
    Vector3 reflection (const Vector3& axis) const;
    Vector3 inTermsOfComponents (const Vector3& i, const Vector3& j, const Vector3& k) const;

    Vector3 rotate (double yaw, double pitch) const;
    Vector3 cross (const Vector3& other) const;
    double length () const;

    double squared () const;
    Vector3 normalize () const;

    double atan2 () const;

    double asin () const;

    friend std::ostream& operator<< (std::ostream& os, const Vector3& vector3);

    double getI () const;
    double getJ () const;
    double getK () const;

    static Vector3 randomInsideUnitSphere ();

    static const Vector3& UP;
    static const Vector3& OUT;
    static const Vector3& SIDE;
};