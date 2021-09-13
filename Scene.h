//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <vector>
#include "Surface.h"
#include "Camera.h"
#include "Intensity.h"
#include "Triangle.h"
#include "SceneObject.h"
#include "LightSource.h"

class Scene {
private:
    std::vector<SceneObject> objects;
    std::vector<LightSource> lightSources;
    Camera camera;
public:
    Scene(std::vector<SceneObject> objects, std::vector<LightSource> lightSources, Camera camera);
    [[nodiscard]] std::vector<std::vector<Intensity>> trace () const;
    [[nodiscard]] Intensity calculate_color(const Ray &ray) const;

//    std::vector<Intersection> getIntersections(const Ray &ray);

    [[nodiscard]] std::optional<Intersection> get_closest_intersection(const Ray &ray) const;
};



