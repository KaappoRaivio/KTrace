//
// Created by kaappo on 12.9.2021.
//
#pragma once

#include "Vector3.h"
#include "Surface.h"
//#include "Surface.h"

struct Surface;

struct Intersection {
    Intersection(double distance, const Vector3 &position, const Surface& Surface) : distance(distance),
                                                                                     position(position),
                                                                                     surface{Surface} {}

    double distance;
    const Vector3& position;
    const Surface& surface;
};