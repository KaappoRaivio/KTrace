cmake_minimum_required(VERSION 3.20)
project(raytracercpp)

set(CMAKE_CXX_STANDARD 23)

SET(CMAKE_BUILD_TYPE Debug)
#set(SDL2_PATH "/usr/lib/SDL2-2.0.16")
find_package(SDL2 REQUIRED SDL2)
#include_directories( ${SDL2_INCLUDE_DIR} )


add_executable(Main main.cpp src/core/interface/MyOpenGLWindow.cpp src/core/interface/MyOpenGLWindow.h src/core/light/Intensity.cpp src/core/light/Intensity.h src/core/common/MyVector3.cpp src/core/common/MyVector3.h src/core/geometry/Ray.cpp src/core/geometry/Ray.h src/core/geometry/Surface.cpp src/core/geometry/Surface.h src/core/geometry/Triangle.cpp src/core/geometry/Triangle.h src/core/geometry/Plane.cpp src/core/geometry/Plane.h src/core/engine/Camera.cpp src/core/engine/Camera.h src/core/engine/Scene.cpp src/core/engine/Scene.h src/core/common/Intersection.h src/core/engine/Material.h src/core/engine/SingleSceneObject.cpp src/core/engine/SingleSceneObject.h src/core/common/LightSource.h src/core/light/IntensityBlend.cpp src/core/light/IntensityBlend.h src/core/light/Color.cpp src/core/light/Color.h src/core/geometry/Sphere.cpp src/core/geometry/Sphere.h src/core/light/SmoothLightSource.cpp src/core/light/SmoothLightSource.h src/core/engine/Texture.cpp src/core/engine/Texture.h src/core/engine/SolidTexture.cpp src/core/engine/SolidTexture.h src/core/engine/Material.cpp lib/stb/std_image.h src/core/engine/ImageTexture.cpp src/core/engine/ImageTexture.h src/core/engine/Image.cpp src/core/engine/Image.h src/core/interface/MyOBJLoader.h src/core/geometry/Mesh.cpp src/core/geometry/Mesh.h src/core/common/mytypes.h src/core/geometry/BVH.cpp src/core/geometry/BVH.h src/core/geometry/AABB.cpp src/core/geometry/AABB.h src/core/geometry/Hittable.h src/core/geometry/Objects.cpp src/core/geometry/Objects.h src/core/engine/SceneObject.h)
#add_executable(OBJ_LOAD load.cpp src/core/interface/MyOBJLoader.h src/core/common/MyVector3.h src/core/common/MyVector3.cpp src/core/engine/SolidTexture.h src/core/engine/SolidTexture.cpp src/core/geometry/Triangle.h src/core/geometry/Triangle.cpp src/core/engine/Camera.h src/core/engine/Camera.cpp src/core/engine/SingleSceneObject.h src/core/engine/SingleSceneObject.cpp src/core/geometry/Plane.h src/core/geometry/Plane.cpp src/core/geometry/Ray.h src/core/geometry/Ray.cpp src/core/light/Intensity.h src/core/light/Intensity.cpp src/core/light/Color.h src/core/light/Color.cpp)
#add_executable(componenttest MyVector3.h MyVector3.cpp)
#add_executable(uvmaptest MyVector3.cpp MyVector3.h Ray.cpp Ray.h Surface.cpp Surface.h Triangle.cpp Triangle.h Plane.cpp Plane.h Intersection.h Material.h SingleSceneObject.cpp SingleSceneObject.h)
#add_executable(imagetest Image.h Image.cpp Intensity.h Intensity.cpp Color.h Color.cpp)

target_link_libraries(Main
        PRIVATE SDL2
        )

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 --std=c++2a")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 --std=c++2a")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 --std=c++2a -fopenmp")




