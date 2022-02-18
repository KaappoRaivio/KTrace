//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <vector>
#include <ostream>
#include "../geometry/Surface.h"
#include "Camera.h"
#include "../light/Intensity.h"
#include "../geometry/Triangle.h"
#include "SingleSceneObject.h"
#include "../common/LightSource.h"
#include "TextureManager.h"

class Scene {
//private:
public:
    std::vector<std::unique_ptr<Surface>> objects;
    std::vector<LightSource> lightSources;
    Camera camera;
    int raysPerPixel;
    int maxBounces;
    int antialiasingScaler;
    TextureManager textureManager;

    Scene (std::vector<std::unique_ptr<Surface>> objects, const std::vector<LightSource>& lightSources, const Camera& camera, int maxBounces, int raysPerPixel, int antialiasingScaler, TextureManager textureManager);
    Scene (const Scene& other) = delete;
    void operator= (const Scene& other) = delete;

    std::vector<std::vector<Intensity>> trace () const;

    Intensity calculate_color (const Ray& ray, int x, int y, int bounces_left, std::stack<double>& opticalDensities) const;

//    std::vector<Intersection> getIntersections(const Ray &ray);

    std::optional<Intersection> get_closest_intersection (const Ray& ray, double max_distance = 0) const;

    static double calculate_beckmann_distribution (const MyVector3& R, const MyVector3& V, double glossiness);

    static double lambertianDiffuseReflection (const MyVector3& N, const MyVector3& L, const MyVector3& d);

    static double orenNayarDiffuseReflection (const MyVector3& face_normal, const MyVector3& vector_to_light, const MyVector3& vector_from_camera, double roughness);

    friend std::ostream& operator<< (std::ostream& os, const Scene& scene);

};



//std::ostream& operator<< (std::ostream& os, const Scene& scene) {
//
//

