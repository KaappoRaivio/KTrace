//
// Created by kaappo on 5.3.2022.
//

#pragma once


template <typename T>
concept Multiplyable =
requires(T a, T b) {
    a.operator*(b);
};

template <typename T>
concept Addable =
requires(T a, T b) {
    a.operator+(b);
};

template<Addable, Multiplyable T>
class Lerp {
private:
    T t0;
    T t1;
public:
    Lerp (T t0, T t1) : t0{t0}, t1{t1} {}
    T operator()(double t) {
        return t0 * t + t1 * (1 - t);
    }
};




