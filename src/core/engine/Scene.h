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
#include "../geometry/Spline.h"

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
    void executeCameraMove (SplineSequence sequence, float deltaT, auto onFrameRendered) {
//        for (float t = 0.1; t < 1; t = sequence.advance(t, deltaT)) {
        for (float t = 0.11; t < 1; t = sequence.advance(t, 0)) {
            if (t >= 1) break;

            Ray currentPose = sequence.apply(t, true);

            if (currentPose.getDirection().x > 0)
                std::cout << "moi" << std::endl;
            std::cout << "t " << t << ", ray " << currentPose <<  std::endl;
            camera.origin = currentPose.getOrigin();
            camera.direction = currentPose.getDirection();
            const auto& pixels = trace();
            onFrameRendered(pixels);
        }
    }

    Intensity calculateColor (const Ray& ray, int x, int y, int bounces_left, std::stack<float>& opticalDensities) const;

//    std::vector<Intersection> getIntersections(const Ray &ray);

    bool getClosestIntersection (const Ray& ray, float max_distance, Intersection& out) const;

    static float calculate_beckmann_distribution (const glm::vec3& R, const glm::vec3& V, float glossiness);
    static float lambertianDiffuseReflection (const glm::vec3& N, const glm::vec3& L, const glm::vec3& d);
    static float orenNayarDiffuseReflection (const glm::vec3& face_normal, const glm::vec3& vector_to_light, const glm::vec3& vector_from_camera, float roughness);
    static float getReflectance (float cosine, float refractionRatio);

    friend std::ostream& operator<< (std::ostream& os, const Scene& scene);

};



//std::ostream& operator<< (std::ostream& os, const Scene& scene) {
//
//

