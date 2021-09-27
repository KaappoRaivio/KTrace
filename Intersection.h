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
    Intersection (double distance, Vector3 position, const SceneObject& surface, Ray ray) : distance(distance), position(std::move(position)), sceneObject{surface}, ray(std::move(ray)) {}

    Intersection (const Intersection& other) = default;

    double distance;
    const Vector3 position;
    const SceneObject& sceneObject;
    const Ray ray;
};