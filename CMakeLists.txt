cmake_minimum_required(VERSION 3.20)
project(cliontest)

set(CMAKE_CXX_STANDARD 20)

#set(SDL2_PATH "/usr/lib/SDL2-2.0.16")
find_package(SDL2 REQUIRED SDL2)
#include_directories( ${SDL2_INCLUDE_DIR} )


add_executable(Main main.cpp MyOpenGLWindow.cpp MyOpenGLWindow.h Intensity.cpp Intensity.h Test.cpp Test.h Vector3.cpp Vector3.h Ray.cpp Ray.h Surface.cpp Surface.h Triangle.cpp Triangle.h Plane.cpp Plane.h Camera.cpp Camera.h Scene.cpp Scene.h Intersection.h Material.h SceneObject.cpp SceneObject.h LightSource.h IntensityBlend.cpp IntensityBlend.h Color.cpp Color.h Sphere.cpp Sphere.h SmoothLightSource.cpp SmoothLightSource.h Texture.cpp Texture.h SolidTexture.cpp SolidTexture.h Material.cpp lib/stb/std_image.h ImageTexture.cpp ImageTexture.h Image.cpp Image.h)
add_executable(componenttest Vector3.h Vector3.cpp)
add_executable(uvmaptest Vector3.cpp Vector3.h Ray.cpp Ray.h Surface.cpp Surface.h Triangle.cpp Triangle.h Plane.cpp Plane.h Intersection.h Material.h SceneObject.cpp SceneObject.h)
#add_executable(imagetest Image.h Image.cpp Intensity.h Intensity.cpp Color.h Color.cpp)

target_link_libraries(Main
        PRIVATE SDL2
        )


#set(CMAKE_CXX_FLAGS_DEBUG "-Os --std=c++2a")
set(CMAKE_CXX_FLAGS_DEBUG "-O3 --std=c++2a -fopenmp")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 --std=c++2a -fopenmp")



