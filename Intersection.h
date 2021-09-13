//
// Created by kaappo on 12.9.2021.
//
#pragma once

#include <utility>

#include "Vector3.h"
#include "Surface.h"
#include "SceneObject.h"
//#include "Surface.h"

class SceneObject;

struct Intersection {
    Intersection(double distance, const Vector3& position, const SceneObject& surface) : distance(distance), position(position), sceneObject{surface} {}
    Intersection(const Intersection& other) = default;

    double distance;
    const Vector3 position;
    const SceneObject& sceneObject;
};