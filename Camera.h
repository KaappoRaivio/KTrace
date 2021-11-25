//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <array>
#include <vector>
#include <ostream>
#include "MyVector3.h"

class Camera {
private:
    inline static const MyVector3 DIRECTION_REFERENCE = {0, 1, 0};

    MyVector3 origin;

    double viewplane_distance;
    std::pair<double, double> viewplane_size;
    std::pair<int, int> viewport_size;

    MyVector3 direction;
    std::pair<double, double> rotation;

public:
    Camera (MyVector3 origin, std::pair<double, double> rotation, double viewplane_distance = 2, std::pair<double, double> viewplane_size = {1, 1}, std::pair<int, int> viewport_size = {80, 80});
    std::vector<std::vector<MyVector3>> get_viewplane (const int i) const;
    const MyVector3& getOrigin () const;
    friend std::ostream& operator<< (std::ostream& os, const Camera& camera);
    void setViewplaneDistance (double viewplaneDistance);
    double getViewplaneDistance () const;
    void move (const MyVector3& direction);

};



