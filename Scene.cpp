//
// Created by kaappo on 11.9.2021.
//

#include "Scene.h"

#include <utility>

Scene::Scene(const std::vector<Surface*>& objects, Camera camera) : objects(std::move(objects)), camera(std::move(camera)) {}

std::vector<std::vector<Color>> Scene::trace() const {
    auto viewplane = camera.get_viewplane();

    std::vector<std::vector<Color>> pixels;
    pixels.reserve(viewplane.size());

    for (int z = 0; z < viewplane.size(); ++z) {
        std::vector<Color> pixel_row;
        pixel_row.reserve(viewplane[z].size());
        for (int x = 0; x < viewplane[z].size(); ++x) {
            const Ray ray = {camera.getOrigin(), viewplane[z][x]};


            pixel_row.push_back(do_raycast(ray) ? Color{1, 0, 0, 1} : Color{0, 0, 0, 1});
        }
        pixels.push_back(pixel_row);
    }

    return pixels;
}

bool Scene::do_raycast(const Ray &ray) const {
    for (auto& object : objects) {
        if (object->get_intersection_distance(ray) != 0) {
//            std::cout << "Hit!" << std::endl;
            return true;
        }
    }
    return false;
}
