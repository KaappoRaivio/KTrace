//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <ostream>
#include <iostream>

class Vector3 {
private:
    double i, j, k;

public:
    Vector3(double i, double j, double k);
    Vector3(const Vector3& other);
    Vector3(Vector3&& original) noexcept ;
    Vector3& operator=(Vector3&& a) noexcept ;
    Vector3& operator=(const Vector3& other) = default;


    Vector3 operator+ (const Vector3& other) const;
    Vector3 operator- () const;
    Vector3 operator- (const Vector3& other) const;
    Vector3 operator* (double other) const;
    double operator* (const Vector3& other) const;
    Vector3 operator/ (double other) const;

    [[nodiscard]] Vector3 rotate (double yaw, double pitch) const;

    [[nodiscard]] Vector3 cross (const Vector3& other) const;
    [[nodiscard]] double length () const;
    [[nodiscard]] double squared () const;
    [[nodiscard]] Vector3 normalize () const;



    friend std::ostream &operator<<(std::ostream &os, const Vector3 &vector3);

    [[nodiscard]] Vector3 reflection(const Vector3 &axis) const;
    static Vector3 randomInsideUnitSphere();
};