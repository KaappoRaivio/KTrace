cmake_minimum_required(VERSION 3.20)
project(raytracercpp)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CONFIGURATION_TYPES "Release; Debug" CACHE STRING "What is this" FORCE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}} /home/kaappo/git/raytracercpp/lib/cmake/modules)



find_package(SDL2 REQUIRED SDL2)
find_package(GLM REQUIRED)
if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
else()
endif(GLM_FOUND)

add_executable(Main main.cpp src/core/interface/MyOpenGLWindow.cpp src/core/interface/MyOpenGLWindow.h src/core/light/Intensity.cpp src/core/light/Intensity.h src/core/common/MyVector3.cpp src/core/common/MyVector3.h src/core/geometry/Ray.cpp src/core/geometry/Ray.h src/core/geometry/Surface.cpp src/core/geometry/Surface.h src/core/geometry/Triangle.cpp src/core/geometry/Triangle.h src/core/geometry/Plane.cpp src/core/geometry/Plane.h src/core/engine/Camera.cpp src/core/engine/Camera.h src/core/engine/Scene.cpp src/core/engine/Scene.h src/core/common/Intersection.h src/core/engine/Material.h src/core/engine/SingleSceneObject.cpp src/core/engine/SingleSceneObject.h src/core/common/LightSource.h src/core/light/IntensityBlend.cpp src/core/light/IntensityBlend.h src/core/light/Color.cpp src/core/light/Color.h src/core/geometry/Sphere.cpp src/core/geometry/Sphere.h src/core/light/SmoothLightSource.cpp src/core/light/SmoothLightSource.h src/core/engine/Texture.cpp src/core/engine/Texture.h src/core/engine/SolidTexture.cpp src/core/engine/SolidTexture.h src/core/engine/Material.cpp lib/stb/std_image.h src/core/engine/ImageTexture.cpp src/core/engine/ImageTexture.h src/core/engine/Image.cpp src/core/engine/Image.h src/core/interface/MyOBJLoader.h src/core/geometry/Mesh.cpp src/core/geometry/Mesh.h src/core/common/mytypes.h src/core/geometry/BVH.cpp src/core/geometry/BVH.h src/core/geometry/AABB.cpp src/core/geometry/AABB.h src/core/geometry/Hittable.h src/core/geometry/Objects.cpp src/core/geometry/Objects.h src/core/engine/SceneObject.h src/core/engine/TextureManager.cpp src/core/engine/TextureManager.h src/core/engine/Scenes.cpp src/core/engine/Scenes.h src/core/common/Intersection.cpp)
target_link_libraries(Main
        PRIVATE SDL2
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++2a")
if(CMAKE_BUILD_TYPE MATCHES  "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -fopenmp -g -fcf-protection=none")
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
endif()

##set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 --std=c++2a")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 --std=c++2a -fopenmp")
##z



