//
// Created by kaappo on 11.9.2021.
//

#include "Scene.h"
#include "Intensity.h"
#include "LightSource.h"
#include "IntensityBlend.h"

#include <utility>
#include <cmath>

Scene::Scene(std::vector<SceneObject> objects, std::vector<LightSource> lightSources, Camera camera)
        : objects(std::move(objects)), camera(std::move(camera)), lightSources(std::move(lightSources)) {}

std::vector<std::vector<Intensity>> Scene::trace() const {
    auto viewplane = camera.get_viewplane();

//    std::vector<std::vector<Intensity>> pixels;
//    pixels.reserve(viewplane.size());

    std::vector<std::vector<Intensity>> pixels;
    pixels.reserve(viewplane.size());
    for (auto & i : viewplane) {

        std::vector<Intensity> row;
        row.reserve(i.size());
        for (int j = 0; j < i.size(); ++j) {
            row.emplace_back(0, 0, 0);
        }
        pixels.push_back(row);
    }

//    std::vector<Intensity> pixel_row;
//    pixel_row.reserve(row.size());

    #pragma omp parallel for collapse(2) default(shared)
    for (int y = 0; y < viewplane.size(); ++y) {
//    for (const auto & row : viewplane) {
//        const auto& row = viewplane[y];

        for (int x = 0; x < viewplane[0].size(); ++x) {
            const auto& pixel = viewplane[y][x];
            const Ray ray = {camera.getOrigin(), pixel};

//            std::cout << calculate_color(ray) << std::endl;

            pixels[y][x] = std::move(calculate_color(ray));
//            pixel_row.push_back(calculate_color(ray, 10 * y + x));
        }
//        pixels.push_back(pixel_row);
    }

    return pixels;
}

Intensity Scene::calculate_color(const Ray &ray) const {
    const auto& intersection = get_closest_intersection(ray);
//    std::cout << intersection.value() << std::endl;

    if (!intersection) {
        return Intensity{0, 0, 0};
    } else {
        const auto closest = *intersection;
//        std::cout << closest.position << std::endl;

//        Intensity diffuse_light = {0, 0, 0};
        IntensityBlend diffuse_light;

        for (const auto& lightSource : lightSources) {
            const Vector3& vector_to_light = lightSource.position - closest.position;
            const Vector3& normalized = vector_to_light.normalize();
            const auto& any_hits = get_closest_intersection({closest.position, normalized});
            if (!any_hits) {
                double dot = std::abs(closest.sceneObject.getSurface()->get_normal_at(closest.position).normalize() *
                                              vector_to_light.normalize());
                double brightness = 1.0 / vector_to_light.squared() * dot;
                diffuse_light += lightSource.intensity * brightness;
            }
        }

        return closest.sceneObject.getMaterial().albedo * diffuse_light.commit_blend();
    }

}

std::optional<Intersection> Scene::get_closest_intersection(const Ray &ray) const {
    std::vector<Intersection> intersections;

    for (const auto& object : objects) {
//        std::cout << "Rayintact: " << ray << std::endl;

        const std::optional<Intersection> possibleIntersection = object.get_intersection(ray);
        if (possibleIntersection) {
//            std::cout << possibleIntersection.value().distance << std::endl;
//            std::cout << possibleIntersection->position << std::endl;
            intersections.push_back(possibleIntersection.value());
        }
    }

    if (intersections.empty()) { return std::nullopt; }
    else {
        Intersection intersection = *std::min_element(intersections.begin(), intersections.end(),
                                                       [](const Intersection &a, const Intersection &b) {
                                                           return a.distance < b.distance;
                                                       });

//        std::cout << intersection.distance << std::endl;
        return intersection;
    }
}
