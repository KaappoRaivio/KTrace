#pragma once

#include <memory>

#include "../../../lib/obj-loader/OBJ_Loader.h"
#include "../engine/Scene.h"
#include <glm/glm.hpp>
#include "../engine/SolidTexture.h"
#include "../geometry/BVH.h"
#include "../geometry/Objects.h"
#include "../common/MyVector3.h"

namespace MyOBJLoader {
    glm::vec3 tovec3 (const objl::Vector3& shittyvector) {
        return {shittyvector.X, shittyvector.Y, shittyvector.Z};
    }

    glm::vec3 tovec3 (const objl::Vector2& shittyvector) {
        return {shittyvector.X, shittyvector.Y, 0};
    }

    std::vector<std::unique_ptr<Surface>> readOBJ (const std::string& path, glm::vec3 positionOffset, float scale, std::pair<float, float> rotationOffset, const Material* material) {
        objl::Loader loader;
        bool success = loader.LoadFile(path);
        if (!success) throw std::runtime_error("Couldn't read obj file!");

        for (int i = 0 ; i < loader.LoadedMeshes.size() ; i++) {
            objl::Mesh& curMesh = loader.LoadedMeshes[i];
            std::cout << "Mesh " << i << ": " << curMesh.MeshName << "\n";
            std::vector<std::unique_ptr<Surface>> objects;

            for (int j = 0 ; j < curMesh.Indices.size() ; j += 3) {
//                auto minimum = tovec3()

                int index1 = curMesh.Indices[j + 0];
                int index2 = curMesh.Indices[j + 1];
                int index3 = curMesh.Indices[j + 2];

                objl::Vertex& vertex1 = curMesh.Vertices[index1];
                objl::Vertex& vertex2 = curMesh.Vertices[index2];
                objl::Vertex& vertex3 = curMesh.Vertices[index3];


                std::cout << "vertex" << j << ": " << std::endl;
                std::cout << glm::to_string(tovec3(vertex1.Position)) << "\t" << glm::to_string(tovec3(vertex2.Position)) << "\t" << glm::to_string(tovec3(vertex3.Position)) << std::endl;
                std::cout << glm::to_string(tovec3(vertex1.TextureCoordinate)) << "\t" << glm::to_string(tovec3(vertex2.TextureCoordinate)) << "\t" << glm::to_string(tovec3(vertex3.TextureCoordinate)) << std::endl;
//                std::cout << glm::to_string(tovec3(vertex1.TextureCoordinate) << "\t" << tovec3(vertex2.TextureCoordinate) << "\t" << tovec3(vertex3.TextureCoordinate)) << std::endl;

                Triangle t{VectorOperations::rotate(tovec3(vertex1.Position), rotationOffset.first, rotationOffset.second) * scale + positionOffset, VectorOperations::rotate(tovec3(vertex2.Position), rotationOffset.first, rotationOffset.second) * scale + positionOffset,
                           VectorOperations::rotate(tovec3(vertex3.Position), rotationOffset.first, rotationOffset.second) * scale + positionOffset, *material,
                           tovec3(vertex1.TextureCoordinate), tovec3(vertex2.TextureCoordinate), tovec3(vertex3.TextureCoordinate)};

                objects.push_back(std::make_unique<Triangle>(t));
            }
            return objects;
        }
        throw std::runtime_error("Lol nope");
    }
}
