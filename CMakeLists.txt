cmake_minimum_required(VERSION 3.20)
project(cliontest)

set(CMAKE_CXX_STANDARD 20)

#set(SDL2_PATH "/usr/lib/SDL2-2.0.16")
find_package(SDL2 REQUIRED SDL2)
#include_directories( ${SDL2_INCLUDE_DIR} )


add_executable(cliontest main.cpp MyOpenGLWindow.cpp MyOpenGLWindow.h Color.cpp Color.h Test.cpp Test.h Vector3.cpp Vector3.h Ray.cpp Ray.h Surface.cpp Surface.h Triangle.cpp Triangle.h Plane.cpp Plane.h Camera.cpp Camera.h Scene.cpp Scene.h)

target_link_libraries(cliontest
    PRIVATE SDL2
)

set(CMAKE_CXX_FLAGS_DEBUG "-O0")



