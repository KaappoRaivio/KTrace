//
// Created by kaappo on 11.9.2021.
//
#include <cmath>

#include "Vector3.h"

Vector3::Vector3(double i, double j, double k) : i(i), j(j), k(k) {}

Vector3 Vector3::operator+(const Vector3 &other) const {
    return {i + other.i, j + other.j, k + other.k};
}

std::ostream &operator<<(std::ostream &os, const Vector3 &vector3) {
    os << "Vector3(" << vector3.i << ", " << vector3.j << ", " << vector3.k << ")";
    return os;
}

Vector3 Vector3::operator-() const {
    return {-i, -j, -k};
}

Vector3 Vector3::operator-(const Vector3 &other) const {
    return *this + -other;
}

Vector3 Vector3::operator*(const double other) const {
    return {other * i, other * j, other * k};
}

Vector3 Vector3::operator/(double other) const {
    return {i / other, j / other, k / other};
}


double Vector3::operator*(const Vector3 &other) const {
    return i * other.i + j * other.j + k * other.k;
}

Vector3 Vector3::cross(const Vector3& other) const {
    return {
        j * other.k - k * other.j,
        k * other.i - i * other.k,
        i * other.j - j * other.i
    };
}

double Vector3::length() const {
    return sqrt(pow(i, 2.0) + pow(j, 2.0) + pow(k, 2.0));
}

Vector3 Vector3::normalize() const {
    return *this / length();
}

Vector3 Vector3::rotate(double yaw, double pitch) const {
    return {
            i * cos(yaw) + (k * sin(pitch) + j * cos(pitch)) * sin(yaw),
            -i * sin(yaw) + (k * sin(pitch) + j * cos(pitch)) * cos(yaw),
            k * cos(pitch) - j * sin(pitch)
    };
}

