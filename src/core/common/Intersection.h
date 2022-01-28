//
// Created by kaappo on 12.9.2021.
//
#pragma once

#include <utility>

#include "MyVector3.h"
#include "../geometry/Surface.h"
#include "../engine/SceneObject.h"
//#include "Surface.h"

class SceneObject;

struct Intersection {
    Intersection (double distance, MyVector3 position, const SceneObject& surface, Ray ray) : distance(distance), position(std::move(position)), sceneObject{surface}, ray(std::move(ray)) {}

    Intersection (const Intersection& other) = default;

    double distance;
    const MyVector3 position;
    const SceneObject& sceneObject;
    const Ray ray;
};