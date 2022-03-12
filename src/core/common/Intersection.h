//
// Created by kaappo on 12.9.2021.
//
#pragma once

#include <utility>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <ostream>
//#include "../engine/materials/Material.h"
#include "../geometry/Ray.h"

class Surface;
class Material;
struct Intersection {
    Intersection () : distance{0}, position{0, 0, 0}, hitSurface{nullptr}, material{nullptr}, ray{{0, 0, 0}, {0, 0, 1}} {}
//    Intersection (double distance, glm::vec3 position, const SingleSceneObject& surface, Ray ray) : distance(distance), position(std::move(position)), sceneObject{surface}, ray(std::move(ray)) {}

//    Intersection (const Intersection& other) = default;


    float distance;
    glm::vec3 position;
//    const SingleSceneObject sceneObject;
    const Surface* hitSurface;
    const Material* material;
    Ray ray;

    friend std::ostream& operator<< (std::ostream& os, const Intersection& intersection);
};

