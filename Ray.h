//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <ostream>
#include "Vector3.h"

class Ray {
public:
    Ray (const Vector3& origin, const Vector3& direction);

private:
    Vector3 origin;
    Vector3 direction;

public:
    const Vector3& getOrigin () const;

    const Vector3& getDirection () const;

    Vector3 apply (double lambda) const;

    friend std::ostream& operator<< (std::ostream& os, const Ray& ray);
};



