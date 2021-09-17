//
// Created by kaappo on 11.9.2021.
//
#include <random>
#include <cmath>
#include <chrono>
#include <cstdlib>

#include "Vector3.h"

Vector3::Vector3(double i, double j, double k) : i(i), j(j), k(k) {}
Vector3::Vector3(const Vector3 &other) = default;
Vector3 &Vector3::operator=(Vector3 &&a) noexcept {
    i = a.i;
    j = a.j;
    k = a.k;
    return *this;
}
Vector3::Vector3(Vector3 &&original)  noexcept : i{original.i}, j{original.j}, k{original.k} {}


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
    return sqrt(squared());
}

double Vector3::squared() const {
    return *this * *this;
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

Vector3 Vector3::reflection(const Vector3 &axis) const {
    return *this - axis * (2 * (*this * axis) / squared());
}

Vector3 Vector3::randomInsideUnitSphere () {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{seed};

    std::normal_distribution<double> d(0, 1);

    double i = d(generator);
    double j = d(generator);
    double k = d(generator);


    const Vector3 &normalized = Vector3(i, j, k).normalize();


    std::uniform_real_distribution<double> dist(0, 1);

    double radius = std::pow(dist(generator), 1.0 / 3.0);
    return normalized * radius;
}


