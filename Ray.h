//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <ostream>
#include "MyVector3.h"

class Ray {
public:
    Ray (const MyVector3& origin, const MyVector3& direction);

private:
    MyVector3 origin;
    MyVector3 direction;

public:
    const MyVector3& getOrigin () const;

    const MyVector3& getDirection () const;

    MyVector3 apply (double lambda) const;

    friend std::ostream& operator<< (std::ostream& os, const Ray& ray);
};



