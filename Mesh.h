#pragma once

#include <vector>
#include "Triangle.h"

class Mesh {
private:
    std::vector<Triangle> triangles;

public:
    Mesh (const std::vector<Triangle>& triangles);
};



