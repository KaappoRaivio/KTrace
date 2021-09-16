//
// Created by kaappo on 11.9.2021.
//

#include "Scene.h"
#include "Intensity.h"
#include "LightSource.h"
#include "IntensityBlend.h"

#include <utility>
#include <cmath>
#include <numbers>

Scene::Scene(std::vector<SceneObject> objects, std::vector<LightSource> lightSources, Camera camera)
        : objects(std::move(objects)), camera(std::move(camera)), lightSources(std::move(lightSources)) {}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
std::vector<std::vector<Intensity>> Scene::trace(int bounces) const {
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


    #pragma omp parallel for collapse(2) default(shared)
    for (int y = 0; y < viewplane.size(); ++y) {
        for (int x = 0; x < viewplane[0].size(); ++x) {
            const auto& pixel = viewplane[y][x];
            const Ray ray = {camera.getOrigin(), pixel};

            pixels[y][x] = std::move(calculate_color(ray, x, y, bounces));
        }
    }

    return pixels;
}
#pragma clang diagnostic pop

Intensity Scene::calculate_color(const Ray &ray, int x, int y, int bounces_left) const {
    const auto& intersection = get_closest_intersection(ray, 0);
//    std::cout << intersection.value() << std::endl;
    if (x == 6 && y == 10) {

//        return {0, 1, 0};
        std::cout << "Gotcha!" << std::endl;
    }


    if (!intersection) {
        return Intensity{0, 0, 0};
    } else {
        const auto closest = *intersection;
//        std::cout << closest.position << std::endl;
        const Material &material = closest.sceneObject.getMaterial();


//        Intensity diffuse_light = {0, 0, 0};
        IntensityBlend diffuse_light;
        IntensityBlend specular_light;
        const Vector3 &face_normal = closest.sceneObject.getSurface()->get_normal_at(closest.position).normalize();

        for (const auto& lightSource : lightSources) {
            const Vector3& vector_to_light = lightSource.position - closest.position;
            const Vector3& V = vector_to_light.normalize();
            const auto& any_hits = get_closest_intersection({closest.position, V}, vector_to_light.length());
            if (!any_hits) {
                double distance_coefficient = 1.0 / vector_to_light.squared();

                double diffuse_direction_coefficient = std::abs(face_normal *vector_to_light.normalize());
//                double specular_direction_coefficient = std::pow(std::abs(closest.ray.getDirection().reflection(face_normal) * V), 16);
                const Vector3 &R = closest.ray.getDirection().reflection(face_normal);

//                double specular_direction_coefficient = std::pow(std::abs(R * V), 16);
                double specular_direction_coefficient = calculate_beckmann_distribution(R.normalize(), V.normalize(), material.glossiness);
                diffuse_light += lightSource.intensity * distance_coefficient * diffuse_direction_coefficient;
                specular_light += lightSource.intensity * distance_coefficient * specular_direction_coefficient;
            }
        }

        if (material.glossiness > 0 && bounces_left > 0) {
            specular_light += calculate_color({closest.position, closest.ray.getDirection().reflection(face_normal).normalize()}, x, y, bounces_left - 1);
        }
        const Intensity &specular_intensity = specular_light.commit_blend();
        const Intensity &diffuse_intensity = diffuse_light.commit_blend();

        return material.albedo * (specular_intensity * material.glossiness + diffuse_intensity * (1 - material.glossiness));
    }

}

std::optional<Intersection> Scene::get_closest_intersection(const Ray &ray, double max_distance) const {
    std::vector<Intersection> intersections;

    for (const auto& object : objects) {
        const std::optional<Intersection> possibleIntersection = object.get_intersection(ray);
        if (possibleIntersection && (max_distance == 0 || possibleIntersection->distance < max_distance)) {
            intersections.push_back(possibleIntersection.value());
        }
    }

    if (intersections.empty()) { return std::nullopt; }
    else {
        Intersection intersection = *std::min_element(intersections.begin(), intersections.end(),
                                                       [](const Intersection &a, const Intersection &b) {
                                                           return a.distance < b.distance;
                                                       });

        return intersection;
    }
}

double Scene::calculate_beckmann_distribution(const Vector3 &R, const Vector3 &V, double glossiness) {
    double roughness = 1 - glossiness;
    if (roughness == 0) {
        return 0;
    }

    double cosine = R * V;

//    std::cout << std::exp(-(1 - std::pow(cosine, 2)) / (std::pow(cosine * glossiness, 2)))
//                 / (std::numbers::pi_v<double> * std::pow(glossiness, 2) * std::pow(cosine, 4)) << std::endl;

    return std::exp(-(1 - std::pow(cosine, 2)) / (std::pow(cosine * roughness, 2)))
        / (std::numbers::pi_v<double> * std::pow(roughness, 2) * std::pow(cosine, 4));
}
