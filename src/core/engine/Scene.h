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
#include "SceneObject.h"
#include "../common/LightSource.h"

class Scene {
//private:
public:
    std::vector<SceneObject> objects;
    std::vector<LightSource> lightSources;
    const Camera& camera;
    int raysPerPixel;
    int antialiasingScaler;
    Scene (const std::vector<SceneObject>& objects, const std::vector<LightSource>& lightSources, const Camera& camera, int raysPerPixel, int antialiasingScaler);

    std::vector<std::vector<Intensity>> trace (int bounces) const;

    Intensity calculate_color (const Ray& ray, int x, int y, int bounces_left) const;

//    std::vector<Intersection> getIntersections(const Ray &ray);

    std::optional<Intersection> get_closest_intersection (const Ray& ray, double max_distance = 0) const;

    static double calculate_beckmann_distribution (const MyVector3& R, const MyVector3& V, double glossiness);

    static double lambertianDiffuseReflection (const MyVector3& face_normal, const MyVector3& vector_to_light, const MyVector3& ray_direction);

    static double orenNayarDiffuseReflection (const MyVector3& face_normal, const MyVector3& vector_to_light, const MyVector3& vector_from_camera, double roughness);

    friend std::ostream& operator<< (std::ostream& os, const Scene& scene);

};

//std::ostream& operator<< (std::ostream& os, const Scene& scene) {
//
//

