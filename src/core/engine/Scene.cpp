//
// Created by kaappo on 11.9.2021.
//

#include "Scene.h"
#include "../light/Intensity.h"
#include "../common/LightSource.h"
#include "../light/IntensityBlend.h"
#include "../common/mytypes.h"
#include "ImageTexture.h"
#include "../geometry/Sphere.h"
//#include "../interface/MyOBJLoader.h"
#include "TextureManager.h"

#include <utility>
#include <cmath>

//#include <numbers>
constexpr double PI = 3.1415926;

Scene::Scene (std::vector<std::unique_ptr<Surface>> objects, const std::vector<LightSource>& lightSources, const Camera& camera, int maxBounces, int raysPerPixel, int antialiasingScaler, TextureManager textureManager)
        : objects{std::move(objects)}, camera(camera), lightSources(std::move(lightSources)), raysPerPixel{raysPerPixel}, antialiasingScaler{antialiasingScaler}, textureManager{std::move(textureManager)}, maxBounces(maxBounces) {}

#pragma clang diagnostic push

std::vector<std::vector<Intensity>> Scene::trace () const {
    auto viewplane = camera.get_viewplane(antialiasingScaler);

    unsigned viewport_height = viewplane.size() / antialiasingScaler;
    unsigned viewport_width = viewplane[0].size() / antialiasingScaler;

    std::vector<std::vector<Intensity>> pixels;
    pixels.reserve(viewport_height);
    for (int y = 0 ; y < viewport_height ; ++y) {
        std::vector<Intensity> row;
        row.reserve(viewport_width);
        for (int x = 0 ; x < viewport_width ; ++x) {
            row.emplace_back(0, 0, 0);
        }
        pixels.push_back(row);
    }


#pragma omp parallel for collapse(2)
//#pragma omp target teams distribute parallel for  collapse(2)
    for (int y = 0 ; y < viewport_height ; ++y) {
        for (int x = 0 ; x < viewport_width ; ++x) {

            IntensityBlend pixelValue;

            for (int dy = 0 ; dy < antialiasingScaler ; ++dy) {
                for (int dx = 0 ; dx < antialiasingScaler ; ++dx) {
                    const auto& pixel = viewplane[y * antialiasingScaler + dy][x * antialiasingScaler + dx];
                    const Ray ray = {camera.getOrigin(), pixel};

                    if (x == 1226 and y == 685)
                        std::cout << "Debug!" << std::endl;

                    std::stack<double> densities;
                    densities.push(1);
                    pixelValue += calculate_color(ray, x + dx, y + dy, maxBounces, densities);
//                    if (DEBUG)
//                        if (densities.size() > 1) std::cout << densities.size() << std::endl;
//                    densities.

                }
            }

            pixels[y][x] = pixelValue.commitBlend();
        }
    }

    return pixels;
}

#pragma clang diagnostic pop

Intensity Scene::calculate_color (const Ray& ray, int x, int y, int bounces_left, std::stack<double>& opticalDensities) const {
    const auto& intersection = get_closest_intersection(ray, 0);
//    std::cout << intersection.value() << std::endl;
    if (DEBUG) {
        if (y % 100 == 0 && x == 0) {
            std::cout << "Row " << y << std::endl;
        }
    }


    if (!intersection) {
        return Intensity{0, 0, 0};
    } else {
#ifdef DEBUG
        std::cout << "hit!" << std::endl;
#endif
        const auto closest = *intersection;
//        std::cout << closest.position << std::endl;
        const Material* material = closest.material;
        const auto* const surface = closest.hitSurface;

        const Intensity& albedo = material->getAlbedoAt(surface->getUVAt(closest.position));

//        Intensity diffuse_light = {0, 0, 0};
        IntensityBlend diffuse_light;
        IntensityBlend specular_light;
        const MyVector3& face_normal = surface->getBumpedNormalAt(closest.position);
        const MyVector3& N = face_normal;

//        if (N * ray.getDirection() >= 0) {
//            return calculate_color({closest.position, ray.getDirection()}, x, y, bounces_left, opticalDensities);
//        }


        const MyVector3& d = closest.ray.getDirection();
        const MyVector3& R = d.reflection(face_normal).normalize();

        for (int i = 0 ; i < raysPerPixel ; ++i) {
            for (const auto& lightSource : lightSources) {
                const MyVector3& vector_to_light = (lightSource.position - closest.position).rotateInsideCone(lightSource.radius);
                const MyVector3& V = vector_to_light.normalize();

                const auto& any_hits = get_closest_intersection({closest.position, V}, vector_to_light.length());

                if (!any_hits) {
                    double distance_coefficient = 1.0 / vector_to_light.squared();

                    double diffuse_direction_coefficient = lambertianDiffuseReflection(N, V, d);
//                    double diffuse_direction_coefficient = orenNayarDiffuseReflection(N, V, R, 1 - material.glossiness);
//                    double diffuse_direction_coefficient = 0;

                    double specular_direction_coefficient = calculate_beckmann_distribution(R, V, material->glossiness);
                    diffuse_light += lightSource.intensity / raysPerPixel * distance_coefficient * diffuse_direction_coefficient;
                    specular_light += lightSource.intensity / raysPerPixel * distance_coefficient * specular_direction_coefficient;
                }
            }
        }

        if (material->glossiness > 0 && bounces_left > 0) {
            specular_light += calculate_color({closest.position, R}, x, y, bounces_left - 1, opticalDensities);
        }


        Intensity underlying{0, 0, 0};
        if (material->alpha < 1 and bounces_left > 0) {
            MyVector3 refracted = surface->refract(closest.position, d.normalize(), opticalDensities).normalize();
//            std::cout << refracted << std::endl;
            underlying = calculate_color({closest.position + refracted * 0.01, refracted}, x, y, bounces_left - 1, opticalDensities);
//            std::cout << underlying << std::endl;
        }

        const Intensity& specular_intensity = specular_light.commitSum();
        const Intensity& diffuse_intensity = diffuse_light.commitSum();

        return albedo * material->alpha * (specular_intensity * material->glossiness + diffuse_intensity * (1 - material->glossiness))
               + underlying * (1 - material->alpha);
    }

}

double Scene::orenNayarDiffuseReflection (const MyVector3& face_normal, const MyVector3& vector_to_light, const MyVector3& vector_from_camera, double roughness) {
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


double Scene::lambertianDiffuseReflection (const MyVector3& N, const MyVector3& L, const MyVector3& d) {
    double dot1 = -d * N;
    double dot2 = L * N;

    if (dot2 > 0 and dot1 > 0) {
        return dot2;
    } else {
        return 0;
    }






//    return std::max(0.0, N * L);

    if ((dot2 < 0) == (dot1 < 0)) {
        return std::abs(N * L);
    } else {
        return 0;
    }

}

std::optional<Intersection> Scene::get_closest_intersection (const Ray& ray, double max_distance) const {
    std::vector<Intersection> intersections;

    for (const auto& object : objects) {
//        std::cout << *object << std::endl;
        const std::optional<Intersection> possibleIntersection = object->getIntersection(ray);
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
//
//
//    double closest_distance = 1e308;
//    Intersection* closest = nullptr;
//
//    for (const auto& object: objects) {
//        std::optional<Intersection> possibleIntersection = object.getIntersection(ray);
//        if (possibleIntersection && possibleIntersection->distance < closest_distance && (max_distance == 0 || possibleIntersection->distance < max_distance)) {
////            std::cout << (*possibleIntersection).sceneObject.getSurface() << std::endl;
//            closest_distance = possibleIntersection->distance;
//            closest = &(*possibleIntersection);
//        }
//    }
//
//    if (closest == nullptr) {
//        return std::nullopt;
//    } else {
//        return {*closest};
//    }
}

double Scene::calculate_beckmann_distribution (const MyVector3& R, const MyVector3& V, double glossiness) {
    double roughness = 1 - glossiness;
    if (roughness == 0) {
        return 0;
    }

    double cosine = R * V;


    return std::exp(-(1 - std::pow(cosine, 2)) / (std::pow(cosine * roughness, 2))) / (PI * std::pow(roughness, 2) * std::pow(cosine, 4));
//    / (std::numbers::pi_v<double> * std::pow(roughness, 2) * std::pow(cosine, 4));


}

std::ostream& operator<< (std::ostream& os, const Scene& scene) {
    os << "objects: {";
    for (const auto& i : scene.objects) {
        os << i << ", ";
    }
    os << "}";

    os << "lightSources: {";
    for (const auto& i : scene.lightSources) {
        os << i << ", ";
    }
    os << "}";

    os << " camera: " << scene.camera << " raysPerPixel: " << scene.raysPerPixel << " antialiasingScaler: " << scene.antialiasingScaler;
    return os;
}

