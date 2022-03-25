//
// Created by kaappo on 11.9.2021.
//

#include "Scene.h"
#include "../light/Intensity.h"
#include "../common/LightSource.h"
#include "../light/IntensityBlend.h"
#include "../common/mytypes.h"
#include "materials/ImageTexture.h"
#include "../geometry/Sphere.h"
//#include "../interface/MyOBJLoader.h"
#include "materials/Manager.h"
#include "../common/MyVector3.h"
#include <glm/gtx/norm.hpp>

#include <utility>
#include <cmath>
#include <iostream>

//#include <numbers>
constexpr float PI = 3.1415926;

Scene::Scene (std::vector<std::unique_ptr<Surface>> objects, const std::vector<LightSource>& lightSources, const Camera& camera, int maxBounces, int raysPerPixel, int antialiasingScaler, Manager<Texture> textureManager, Manager<Material> materialManager)
        : objects{std::move(objects)}, lightSources(std::move(lightSources)), camera(camera), raysPerPixel{raysPerPixel}, maxBounces(maxBounces), antialiasingScaler{antialiasingScaler}, textureManager{std::move(textureManager)}, materialManager{std::move(materialManager)} {}

#pragma clang diagnostic push
//#pragma omp declare target

std::vector<std::vector<Intensity>> Scene::trace () const {
    auto viewplane = camera.getViewplane(antialiasingScaler);

    unsigned viewport_height = viewplane.size() / antialiasingScaler;
    unsigned viewport_width = viewplane[0].size() / antialiasingScaler;

    std::vector<std::vector<Intensity>> pixels;
    pixels.reserve(viewport_height);
    for (size_t y = 0 ; y < viewport_height ; ++y) {
        std::vector<Intensity> row;
        row.reserve(viewport_width);
        for (size_t x = 0 ; x < viewport_width ; ++x) {
            row.emplace_back(0, 0, 0);
        }
        pixels.push_back(row);
    }


#pragma omp parallel for collapse(2)
//#pragma omp target map(to:viewplane), map(tofrom:pixels)
//teams distribute parallel for  collapse(2)
    for (size_t y = 0 ; y < viewport_height ; ++y) {
        for (size_t x = 0 ; x < viewport_width ; ++x) {

            IntensityBlend pixelValue;

            for (int dy = 0 ; dy < antialiasingScaler ; ++dy) {
                for (int dx = 0 ; dx < antialiasingScaler ; ++dx) {
                    const auto& pixel = viewplane[y * antialiasingScaler + dy][x * antialiasingScaler + dx];
                    const Ray ray = {camera.getOrigin(), pixel};

//                    if (x == 2 and y == 2)
//                        std::cout << "Debug!" << std::endl;

                    std::stack<float> densities;
                    densities.push(1);
                    pixelValue += calculateColor(ray, x + dx, y + dy, maxBounces, densities);

//                    if (DEBUG)
//                        std::cout << densities.size() << std::endl;
//                    densities.

                }
            }

            pixels[y][x] = pixelValue.commitBlend();
        }
    }

    return pixels;
}

#pragma clang diagnostic pop
Intensity Scene::calculateColor (const Ray& ray, int x, int y, int bounces_left, std::stack<float>& opticalDensities) const {
    Intersection intersection;
    bool intersects = getClosestIntersection(ray, 0, intersection);
//    std::cout << intersection.value() << std::endl;

    if (x == 573 && y == 513) {
        std::cout << "debug" << std::endl;
    }

    if constexpr(DEBUG) {
        if (y % 100 == 0 && x == 0) {
            std::cout << "Row " << y << std::endl;
        }
    }


    if (not intersects) {
        return Intensity{0, 0, 0};
    } else {
//        return Intensity{0, 1, 0};

    if constexpr(DEBUG) {
        std::cout << "hit!" << std::endl;
    }

        //        std::cout << closest.position << std::endl;
        const Material* material = intersection.material;
        const auto* const surface = intersection.hitSurface;

        const Intensity& albedo = material->getAlbedoAt(surface->getUVAt(intersection.position));

//        Intensity diffuse_light = {0, 0, 0};
        IntensityBlend diffuse_light;
        IntensityBlend specular_light;
        const glm::vec3& face_normal = surface->getBumpedNormalAt(intersection.position);
        const glm::vec3& N = face_normal;


        const glm::vec3& d = intersection.ray.getDirection();
        const glm::vec3& R = glm::normalize(glm::reflect(d, face_normal));

        std::vector<LightSource> visibleLightSources;

        IntensityBlend simpleShaded;

        for (int i = 0 ; i < raysPerPixel ; ++i) {
            for (const auto& lightSource : lightSources) {
                const glm::vec3& vector_to_light = VectorOperations::rotateInsideCone(lightSource.position - intersection.position, lightSource.radius);
                const glm::vec3& V = glm::normalize(vector_to_light);

                Intersection _;
                bool anyHits = getClosestIntersection({intersection.position, V}, vector_to_light.length(), _);

                if (not anyHits) {
                    visibleLightSources.push_back(lightSource);
                }
            }
            simpleShaded += material->shade(intersection.position, N, intersection, visibleLightSources);
        }
        IntensityBlend scatterShaded;

        if (bounces_left > 0) {
            std::array<Interface, 10> scatteredRays{};

            int numberOfRays = material->scatter(intersection.position, N, intersection, opticalDensities, scatteredRays);
            for (int i = 0; i < numberOfRays; ++i) {
                const auto& interface = scatteredRays[i];
                scatterShaded += interface.intensity * calculateColor(interface.ray, x, y, bounces_left - 1, opticalDensities);
            }
        }

        return simpleShaded.commitBlend() + scatterShaded.commitSum();
    }

}

float Scene::orenNayarDiffuseReflection (const glm::vec3& face_normal, const glm::vec3& vector_to_light, const glm::vec3& vector_from_camera, float roughness) {
    const auto& n = glm::normalize(face_normal);
    const auto& v = glm::normalize(vector_to_light);
    const auto& d = glm::normalize(vector_from_camera);
    float sigma = roughness;
    float variance = std::pow(sigma, 2);

    float s = glm::dot(n, v) * glm::dot(d, n) - glm::dot(v, d);
    float t = s > 0 ? std::max(glm::dot(n, v), -glm::dot(n, d)) : 1;

    float A = 1 / M_PI * (1 - 0.5 * variance / (variance + 0.17) * variance / (variance + 0.13));
    float B = 1 / M_PI * (0.45 * variance / (variance + 0.09));

    float d1 = glm::dot(d, n) * (A + B * s / t);
//    std::cout << d1 << std::endl;
    return std::clamp(d1, 0.0f, 1.0f);
}




bool Scene::getClosestIntersection (const Ray& ray, float max_distance, Intersection& out) const {
    std::vector<Intersection> intersections;

    for (const auto& object : objects) {
//        std::cout << *object << std::endl;
        Intersection temp;
        bool intersects = object->getIntersection(ray, temp);
        if (intersects && (max_distance == 0 || temp.distance < max_distance)) {
            intersections.push_back(temp);
        }
    }

    if (intersections.empty()) { return false; }
    else {
        Intersection intersection = *std::min_element(intersections.begin(), intersections.end(), [] (const Intersection& a, const Intersection& b) {
            return a.distance < b.distance;
        });

        out = intersection;
        return true;
    }
//
//
//    float closest_distance = 1e308;
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





std::ostream& operator<< (std::ostream& os, const Scene& scene) {
    os << "objects: {";
    for (const auto& i : scene.objects) {
        os << *i << ", ";
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

//void Scene::executeCameraMove (SplineSequence sequence, float deltaT, auto onFrameRendered) {
//    for (float t = 0; t < 1; t += deltaT) {
//        camera.origin = sequence.apply(t).getOrigin();
//        camera.direction = sequence.apply(t).getDirection();
//        auto&& pixels = trace();
//        onFrameRendered(std::move(pixels));
//    }
//}

//#pragma omp end declare target
