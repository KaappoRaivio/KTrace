//
// Created by kaappo on 28.1.2022.
//

#pragma once


#include "Hittable.h"
#include "AABB.h"

class BVHNode : public Hittable {

private:
    AABB box;

};



