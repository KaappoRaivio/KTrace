//
// Created by kaappo on 11.9.2021.
//

#include "Scene.h"
#include "Intensity.h"
#include "LightSource.h"
#include "IntensityBlend.h"

#include <utility>
#include <cmath>

//#include <numbers>
constexpr double PI = 3.1415926;

Scene::Scene (const std::vector<SceneObject>& objects, const std::vector<LightSource>& lightSources, Camera camera, int raysPerPixel, int antialiasingScaler) : objects(std::move(objects)), camera(std::move(camera)), lightSources(std::move(lightSources)), raysPerPixel{raysPerPixel}, antialiasingScaler{antialiasingScaler} {}

#pragma clang diagnostic push

std::vector<std::vector<Intensity>> Scene::trace (int bounces) const {
    auto viewplane = camera.get_viewplane(antialiasingScaler);

    unsigned viewport_height = viewplane.size() / antialiasingScaler;
    unsigned viewport_width = viewplane[0].size() / antialiasingScaler;

    std::vector<std::vector<Intensity>> pixels;
    pixels.reserve(viewport_height);
    for (int y = 0; y < viewport_height; ++y) {
        std::vector<Intensity> row;
        row.reserve(viewport_width);
        for (int x = 0; x < viewport_width; ++x) {
            row.emplace_back(0, 0, 0);
        }
        pixels.push_back(row);
    }


#pragma omp parallel for collapse(2)
    for (int y = 0; y < viewport_height; ++y) {
        for (int x = 0; x < viewport_width; ++x) {

            IntensityBlend pixelValue;

            for (int dy = 0; dy < antialiasingScaler; ++dy) {
                for (int dx = 0; dx < antialiasingScaler; ++dx) {
                    const auto& pixel = viewplane[y * antialiasingScaler + dy][x * antialiasingScaler + dx];
                    const Ray ray = {camera.getOrigin(), pixel};

                    pixelValue += calculate_color(ray, x + dx, y + dy, bounces);

                }
            }

            pixels[y][x] = pixelValue.commitBlend();
        }
    }

    return pixels;
}

#pragma clang diagnostic pop

Intensity Scene::calculate_color (const Ray& ray, int x, int y, int bounces_left) const {
    const auto& intersection = get_closest_intersection(ray, 0);
//    std::cout << intersection.value() << std::endl;
    if (y % 100 == 0 && x == 0) {

//        return {0, 1, 0};
        std::cout << "Row " << y << std::endl;
    }


    if (!intersection) {
        return Intensity{0, 0, 0};
    } else {
        const auto closest = *intersection;
//        std::cout << closest.position << std::endl;
        const Material& material = closest.sceneObject.getMaterial();
        const auto* const surface = closest.sceneObject.getSurface();

        const Intensity& albedo = material.get_albedo_at(surface->get_uv_at(closest.position));

//        Intensity diffuse_light = {0, 0, 0};
        IntensityBlend diffuse_light;
        IntensityBlend specular_light;
        const Vector3& face_normal = surface->get_normal_at(closest.position).normalize();
        const Vector3& N = face_normal;

        const Vector3& d = closest.ray.getDirection();
        const Vector3& R = d.reflection(face_normal).normalize();
        for (int i = 0; i < raysPerPixel; ++i) {
            for (const auto& lightSource: lightSources) {
                const Vector3& vector_to_light = (lightSource.position - closest.position).rotateInsideCone(lightSource.radius);
                const Vector3& V = vector_to_light.normalize();

                const auto& any_hits = get_closest_intersection({closest.position, V}, vector_to_light.length());

                if (!any_hits) {
                    double distance_coefficient = 1.0 / vector_to_light.squared();

                    double diffuse_direction_coefficient = lambertianDiffuseReflection(N, V, d);
//                    double diffuse_direction_coefficient = orenNayarDiffuseReflection(N, V, R, 1 - material.glossiness);
//                    double diffuse_direction_coefficient = 0;



                    //                double specular_direction_coefficient = std::pow(std::abs(closest.ray.getDirection().reflection(face_normal) * V), 16);

//                double specular_direction_coefficient = std::pow(std::abs(R * V), 16);
                    double specular_direction_coefficient = calculate_beckmann_distribution(R, V, material.glossiness);
                    diffuse_light += lightSource.intensity / raysPerPixel * distance_coefficient * diffuse_direction_coefficient;
                    specular_light += lightSource.intensity / raysPerPixel * distance_coefficient * specular_direction_coefficient;
                }
            }
        }

        if (material.glossiness > 0 && bounces_left > 0) {
            specular_light += calculate_color({closest.position, R}, x, y, bounces_left - 1);
        }
        const Intensity& specular_intensity = specular_light.commitSum();
        const Intensity& diffuse_intensity = diffuse_light.commitSum();

        return albedo * (specular_intensity * material.glossiness + diffuse_intensity * (1 - material.glossiness));
    }

}

double Scene::orenNayarDiffuseReflection (const Vector3& face_normal, const Vector3& vector_to_light, const Vector3& vector_from_camera, double roughness) {
    const auto& n = face_normal.normalize();
    const auto& v = vector_to_light.normalize();
    const auto& d = vector_from_camera.normalize();
    double sigma = roughness;
    double variance = std::pow(sigma, 2);

    double s = (n * v) * (d * n) - v * d;
    double t = s > 0 ? std::max(n * v, -n * d) : 1;

    double A = 1 / M_PI * (1 - 0.5 * variance / (variance + 0.17) * variance / (variance + 0.13));
    double B = 1 / M_PI * (0.45 * variance / (variance + 0.09));

    double d1 = d * n * (A + B * s / t);
//    std::cout << d1 << std::endl;
    return std::clamp(d1, 0.0, 1.0);
}


double Scene::lambertianDiffuseReflection (const Vector3& face_normal, const Vector3& vector_to_light, const Vector3& ray_direction) {
    double dot1 = -ray_direction * face_normal;
    double dot2 = vector_to_light * face_normal;

    if ((dot2 < 0) == (dot1 < 0)) {
        return std::abs(face_normal * vector_to_light);
    } else {
        return 0;
    }

}

std::optional<Intersection> Scene::get_closest_intersection (const Ray& ray, double max_distance) const {
    std::vector<Intersection> intersections;

    for (const auto& object: objects) {
        const std::optional<Intersection> possibleIntersection = object.get_intersection(ray);
        if (possibleIntersection && (max_distance == 0 || possibleIntersection->distance < max_distance)) {
            intersections.push_back(possibleIntersection.value());
        }
    }

    if (intersections.empty()) { return std::nullopt; }
    else {
        Intersection intersection = *std::min_element(intersections.begin(), intersections.end(), [] (const Intersection& a, const Intersection& b) {
            return a.distance < b.distance;
        });

        return intersection;
    }
}

double Scene::calculate_beckmann_distribution (const Vector3& R, const Vector3& V, double glossiness) {
    double roughness = 1 - glossiness;
    if (roughness == 0) {
        return 0;
    }

    double cosine = R * V;


    return std::exp(-(1 - std::pow(cosine, 2)) / (std::pow(cosine * roughness, 2))) / (PI * std::pow(roughness, 2) * std::pow(cosine, 4));
//    / (std::numbers::pi_v<double> * std::pow(roughness, 2) * std::pow(cosine, 4));


}
