//#include <iostream>
//#include "lib/obj-loader/OBJ_Loader.h"
//#include "Triangle.h"
#include "core/interface/MyOBJLoader.h"

extern const double PRECISION_LIMIT = 0.001;


int main () {
//    MyOBJLoader::readOBJ("../untitled.obj");
    Triangle t = {{0, 0, 0}, {10, 0, 0}, {0, 10, 0}};
    std::cout << t.get_uv_at({3, 3, 0}) << std::endl;
    return 0;
}