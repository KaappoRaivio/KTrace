//
// Created by kaappo on 12.9.2021.
//
#pragma once

#include <utility>

#include "MyVector3.h"
#include "../geometry/Surface.h"
#include "../engine/SingleSceneObject.h"
//#include "Surface.h"

class SingleSceneObject;

struct Intersection {
//    Intersection (double distance, MyVector3 position, const SingleSceneObject& surface, Ray ray) : distance(distance), position(std::move(position)), sceneObject{surface}, ray(std::move(ray)) {}

//    Intersection (const Intersection& other) = default;


    const double distance;
    const MyVector3 position;
//    const SingleSceneObject sceneObject;
    const Surface* hitSurface;
    const Material* material;
    const Ray ray;
};