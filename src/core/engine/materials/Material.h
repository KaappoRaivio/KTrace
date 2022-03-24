//
// Created by kaappo on 12.9.2021.
//

#pragma once

#include <memory>
#include <ostream>
#include <glm/glm.hpp>
#include <vector>
#include <stack>
#include "../../light/Intensity.h"
#include "Texture.h"
#include "SolidTexture.h"
#include "../../common/Interface.h"
#include "../../common/LightSource.h"
#include "../../common/Intersection.h"


typedef const glm::vec3& vec;

class Material {
protected:
    const Texture* albedo;
    const Texture* bump;
    Intensity emittance;
protected:
    Material (const Texture* albedo, const Texture* bump, const Intensity& emittance);
    Material (const Texture* albedo, const Texture* bump);
    Material (const Texture* albedo);
    Material ();

public:
    virtual Intensity getAlbedoAt (vec uv) const;
    virtual glm::vec3 getNormalAt (const glm::vec3& uv, const glm::vec3& normal) const;
//    virtual Intensity getBumpedNormalAt (vec uv) const {
//        return getNormalAt(uv, <#initializer#>);
//    }
    virtual Intensity emit () const {
        return emittance;
    };

    friend std::ostream& operator<< (std::ostream& os, const Material& material);

    virtual int scatter (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, std::stack<float>& opticalDensities, std::array<Interface, 10>& scatteredRays) const = 0;
    virtual Intensity shade (const glm::vec3& position, const glm::vec3& normal, const Intersection& intersection, const std::vector<LightSource>& visibleLightSources) const = 0;
    virtual std::ostream& print (std::ostream& s) const = 0;
};

//struct Material {
//    const Texture* albedo;
//    const Texture* bump;
//    double glossiness;
//    double alpha = 1;
//    double opticalDensity = 1;
//
//    constexpr Material (const Texture* const albedo, double glossiness, const Texture* bump) : albedo{albedo}, bump{bump}, glossiness{glossiness} {}
//    constexpr Material (const Texture* const albedo, double glossiness, double alpha) : albedo{albedo}, bump{&SolidTextures::BUMP_UP}, glossiness{glossiness}, alpha{alpha} {}
//    explicit Material (const Texture* const albedo) : albedo{albedo}, bump{&SolidTextures::BUMP_UP}, glossiness{0}, alpha{1} {}
//
//public:
//    Intensity getAlbedoAt (const glm::vec3& uv) const;
//
//    glm::vec3 getBumpAt (const glm::vec3& uv, const glm::vec3& normal) const;
//
//    friend std::ostream& operator<< (std::ostream& os, const Material& material);
//};


namespace Materials {
//    constexpr Material WHITE_GLOSSY{&SolidTextures::WHITE, 0.8, 1};
//    constexpr Material BLUE_GLOSSY{&SolidTextures::BLUE, 0.8, 1};
//    constexpr Material BLUE{&SolidTextures::BLUE, 0, 1};
//    constexpr Material RED_GLOSSY{&SolidTextures::RED, 0.6, 1};
//    constexpr Material YELLOW_GLOSSY{&SolidTextures::YELLOW, 0.8, 1};
//    constexpr Material GREEN_GLOSSY{&SolidTextures::GREEN, 0.8, 1};
//    constexpr Material WHITE{&SolidTextures::WHITE, 0, 1};
}