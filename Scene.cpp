//
// Created by kaappo on 11.9.2021.
//

#include "Scene.h"
#include "Intensity.h"

#include <utility>
#include <cmath>

Scene::Scene(std::vector<SceneObject>  objects, Camera camera) : objects(std::move(objects)), camera(std::move(camera)) {}

std::vector<std::vector<Color>> Scene::trace() const {
    auto viewplane = camera.get_viewplane();

    std::vector<std::vector<Color>> pixels;
    pixels.reserve(viewplane.size());

    for (int z = 0; z < viewplane.size(); ++z) {
        std::vector<Color> pixel_row;
        pixel_row.reserve(viewplane[z].size());
        for (int x = 0; x < viewplane[z].size(); ++x) {
            const Ray ray = {camera.getOrigin(), viewplane[z][x]};


            pixel_row.push_back(calculate_color(ray));
        }
        pixels.push_back(pixel_row);
    }

    return pixels;
}

Color Scene::calculate_color(const Ray &ray) const {
    for (const auto& object : objects) {
        const std::optional<Intersection> &possibleIntersection = object.getSurface().get_intersection_distance(ray);
        if (possibleIntersection) {
//            std::cout << "Hit!" << std::endl;
//            return true;
            double dot = std::abs(ray.getDirection().normalize() *
                         possibleIntersection->surface.get_normal_at(possibleIntersection->position).normalize());
//            std::cout << dot << std::endl;
            double brightness = 1.0 / std::pow(possibleIntersection->distance, 2) * dot;
            return object.getMaterial().albedo * brightness * 50.0;
        }
    }
    return Intensity{0, 0, 0};
}
