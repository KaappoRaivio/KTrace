//
// Created by kaappo on 11.9.2021.
//
#include <random>
#include <cmath>
#include <chrono>
#include <cstdlib>

#include "MyVector3.h"



MyVector3 MyVector3::operator+ (const MyVector3& other) const {
    return {i + other.i, j + other.j, k + other.k};
}

std::ostream& operator<< (std::ostream& os, const MyVector3& vector3) {
    os << "MyVector3(" << vector3.i << ", " << vector3.j << ", " << vector3.k << ")";
    return os;
}

MyVector3 MyVector3::operator- () const {
    return {-i, -j, -k};
}

MyVector3 MyVector3::operator- (const MyVector3& other) const {
    return *this + -other;
}

MyVector3 MyVector3::operator* (const double other) const {
    return {other * i, other * j, other * k};
}

MyVector3 MyVector3::operator/ (double other) const {
    return {i / other, j / other, k / other};
}


double MyVector3::operator* (const MyVector3& other) const {
    return i * other.i + j * other.j + k * other.k;
}

MyVector3 MyVector3::cross (const MyVector3& other) const {
    return {j * other.k - k * other.j, k * other.i - i * other.k, i * other.j - j * other.i};
}

double MyVector3::length () const {
    return sqrt(squared());
}

double MyVector3::squared () const {
    return *this * *this;
}

MyVector3 MyVector3::normalize () const {
    return *this / length();
}

MyVector3 MyVector3::rotate (double yaw, double pitch) const {
    return {i * cos(yaw) + (k * sin(pitch) + j * cos(pitch)) * sin(yaw), -i * sin(yaw) + (k * sin(pitch) + j * cos(pitch)) * cos(yaw), k * cos(pitch) - j * sin(pitch)};
}

MyVector3 MyVector3::reflection (const MyVector3& axis) const {
    return *this - axis * (2 * (*this * axis) / squared());
}

MyVector3 MyVector3::randomInsideUnitSphere () {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{seed};

    std::normal_distribution<double> d(0, 1);

    double i = d(generator);
    double j = d(generator);
    double k = d(generator);


    const MyVector3& normalized = MyVector3(i, j, k).normalize();


    std::uniform_real_distribution<double> dist(0, 1);

    double radius = std::pow(dist(generator), 1.0 / 3.0);
    return normalized * radius;
}

MyVector3 MyVector3::inTermsOfComponents (const MyVector3& i, const MyVector3& j, const MyVector3& k) const {
    Eigen::Matrix3d A;
    A << i.i, i.j, i.k, j.i, j.j, j.k, k.i, k.j, k.k;
    A.transposeInPlace();

    Eigen::Vector3d b;
    b << this->i, this->j, this->k;
    Eigen::Vector3d x = A.colPivHouseholderQr().solve(b);

    return {x[0], x[1], x[2]};
}

MyVector3 MyVector3::rotateInsideCone (double radius) const {
    if (radius == 0) {
        return *this;
    }

    const MyVector3& tangent = cross(MyVector3::UP).normalize();
    const MyVector3& bitangent = cross(tangent).normalize();

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

MyVector3::operator bool () const {
    return squared() != 0;
}

MyVector3 MyVector3::operator|| (const MyVector3& other) const {
    return bool(*this) ? *this : other;
}

double MyVector3::atan2 () const {
    return std::atan2(i, j);
}

double MyVector3::asin () const {
    return std::asin(k);
}

const MyVector3& MyVector3::UP = {0, 0, 1};

const MyVector3& MyVector3::OUT = {0, 1, 0};

const MyVector3& MyVector3::SIDE = {1, 0, 0};

double MyVector3::getI () const {
    return i;
}

double MyVector3::getJ () const {
    return j;
}

double MyVector3::getK () const {
    return k;
}

double MyVector3::dot (const MyVector3& other) const {
//    return 0;
    return i * other.i + j * other.j + k * other.k;
}

double MyVector3::operator[] (int index) const {
    switch (index) {
        case 0:
            return i;
        case 1:
            return j;
        case 2:
            return k;
        default:
            std::stringstream ss;
            ss << "Invalid dimension " << index << "!";
            throw std::runtime_error(ss.str());
    }
}

bool MyVector3::operator== (const MyVector3& rhs) const {
    return i == rhs.i &&
           j == rhs.j &&
           k == rhs.k;
}

bool MyVector3::operator!= (const MyVector3& rhs) const {
    return !(rhs == *this);
}

//int main () {
//    std::cout << "Hello, world" << std::endl;
//
//    MyVector3 a = {0, 0, 1};
//
//    MyVector3 i = {1, 0, 0};
//    MyVector3 j = {1, 1, 0};
//    MyVector3 k = {1, 0, 1};
//
//    std::cout << a.inTermsOfComponents(i, j, k) << std::endl;
//}