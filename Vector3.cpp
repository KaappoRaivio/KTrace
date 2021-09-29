//
// Created by kaappo on 11.9.2021.
//
#include <random>
#include <cmath>
#include <chrono>
#include <cstdlib>

#include "Vector3.h"

Vector3::Vector3 (double i, double j, double k) : i(i), j(j), k(k) {}


Vector3 Vector3::operator+ (const Vector3& other) const {
    return {i + other.i, j + other.j, k + other.k};
}

std::ostream& operator<< (std::ostream& os, const Vector3& vector3) {
    os << "Vector3(" << vector3.i << ", " << vector3.j << ", " << vector3.k << ")";
    return os;
}

Vector3 Vector3::operator- () const {
    return {-i, -j, -k};
}

Vector3 Vector3::operator- (const Vector3& other) const {
    return *this + -other;
}

Vector3 Vector3::operator* (const double other) const {
    return {other * i, other * j, other * k};
}

Vector3 Vector3::operator/ (double other) const {
    return {i / other, j / other, k / other};
}


double Vector3::operator* (const Vector3& other) const {
    return i * other.i + j * other.j + k * other.k;
}

Vector3 Vector3::cross (const Vector3& other) const {
    return {j * other.k - k * other.j, k * other.i - i * other.k, i * other.j - j * other.i};
}

double Vector3::length () const {
    return sqrt(squared());
}

double Vector3::squared () const {
    return *this * *this;
}

Vector3 Vector3::normalize () const {
    return *this / length();
}

Vector3 Vector3::rotate (double yaw, double pitch) const {
    return {i * cos(yaw) + (k * sin(pitch) + j * cos(pitch)) * sin(yaw), -i * sin(yaw) + (k * sin(pitch) + j * cos(pitch)) * cos(yaw), k * cos(pitch) - j * sin(pitch)};
}

Vector3 Vector3::reflection (const Vector3& axis) const {
    return *this - axis * (2 * (*this * axis) / squared());
}

Vector3 Vector3::randomInsideUnitSphere () {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{seed};

    std::normal_distribution<double> d(0, 1);

    double i = d(generator);
    double j = d(generator);
    double k = d(generator);


    const Vector3& normalized = Vector3(i, j, k).normalize();


    std::uniform_real_distribution<double> dist(0, 1);

    double radius = std::pow(dist(generator), 1.0 / 3.0);
    return normalized * radius;
}

Vector3 Vector3::inTermsOfComponents (const Vector3& i, const Vector3& j, const Vector3& k) const {
    Eigen::Matrix3d A;
    A << i.i, i.j, i.k, j.i, j.j, j.k, k.i, k.j, k.k;
    A.transposeInPlace();

    Eigen::Vector3d b;
    b << this->i, this->j, this->k;
    Eigen::Vector3d x = A.colPivHouseholderQr().solve(b);

    return {x[0], x[1], x[2]};
}

Vector3 Vector3::rotateInsideCone (double radius) const {

    const Vector3& tangent = cross(Vector3::UP).normalize();
    const Vector3& bitangent = cross(tangent).normalize();

    const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{seed};

    std::normal_distribution<double> normalDistribution(0, 1);
    std::uniform_real_distribution<double> uniformRealDistribution(0, 1);
    std::uniform_real_distribution<double> angleDistribution(0, 2 * M_PI);

    double scatterRadius = std::pow(angleDistribution(generator), 1 / 2.0) * radius;

    double angle = angleDistribution(generator);
    double x = std::cos(angle) * scatterRadius;
    double y = std::sin(angle) * scatterRadius;


    return tangent * x + bitangent * y + *this;

}

Vector3::operator bool () const {
    return squared() != 0;
}

Vector3 Vector3::operator|| (const Vector3& other) const {
    return bool(*this) ? *this : other;
}

double Vector3::atan2 () const {
    return std::atan2(i, j);
}

double Vector3::asin () const {
    return std::asin(k);
}

const Vector3& Vector3::UP = {0, 0, 1};

const Vector3& Vector3::OUT = {0, 1, 0};

const Vector3& Vector3::SIDE = {1, 0, 0};

double Vector3::getI () const {
    return i;
}

double Vector3::getJ () const {
    return j;
}

double Vector3::getK () const {
    return k;
}

//int main () {
//    std::cout << "Hello, world" << std::endl;
//
//    Vector3 a = {0, 0, 1};
//
//    Vector3 i = {1, 0, 0};
//    Vector3 j = {1, 1, 0};
//    Vector3 k = {1, 0, 1};
//
//    std::cout << a.inTermsOfComponents(i, j, k) << std::endl;
//}