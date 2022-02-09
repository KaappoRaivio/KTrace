#pragma once

#include <memory>

#include "../../../lib/obj-loader/OBJ_Loader.h"
#include "../engine/Scene.h"
#include "../common/MyVector3.h"
#include "../engine/SolidTexture.h"
#include "../geometry/BVH.h"
#include "../geometry/Objects.h"

namespace MyOBJLoader {
    MyVector3 toMyVector3 (const objl::Vector3& shittyvector) {
        return {shittyvector.X, shittyvector.Y, shittyvector.Z};
    }

    MyVector3 toMyVector3 (const objl::Vector2& shittyvector) {
        return {shittyvector.X, shittyvector.Y, 0};
    }

    std::vector<std::unique_ptr<Surface>> readOBJ (const std::string& path, MyVector3 positionOffset, double scale, std::pair<double, double> rotationOffset, const Material* material) {
        objl::Loader loader;
        bool success = loader.LoadFile(path);
        if (!success) throw std::runtime_error("Couldn't read obj file!");

        for (int i = 0 ; i < loader.LoadedMeshes.size() ; i++) {
            objl::Mesh& curMesh = loader.LoadedMeshes[i];
            std::cout << "Mesh " << i << ": " << curMesh.MeshName << "\n";
//            std::cout << curMesh.MeshMaterial.map_Kd << std::endl;

//            auto color = Material{std::make_shared<ImageTexture>("../res/texture3.png")};
            std::vector<std::unique_ptr<Surface>> objects;

            for (int j = 0 ; j < curMesh.Indices.size() ; j += 3) {
//                auto minimum = toMyVector3()

                double index1 = curMesh.Indices[j + 0];
                double index2 = curMesh.Indices[j + 1];
                double index3 = curMesh.Indices[j + 2];

                objl::Vertex& vertex1 = curMesh.Vertices[index1];
                objl::Vertex& vertex2 = curMesh.Vertices[index2];
                objl::Vertex& vertex3 = curMesh.Vertices[index3];


                std::cout << "vertex" << j << ": " << std::endl;
                std::cout << toMyVector3(vertex1.Position) << "\t" << toMyVector3(vertex2.Position) << "\t" << toMyVector3(vertex3.Position) << std::endl;
                std::cout << toMyVector3(vertex1.TextureCoordinate) << "\t" << toMyVector3(vertex2.TextureCoordinate) << "\t" << toMyVector3(vertex3.TextureCoordinate) << std::endl;

                Triangle t{toMyVector3(vertex1.Position).rotate(rotationOffset.first, rotationOffset.second) * scale + positionOffset, toMyVector3(vertex2.Position).rotate(rotationOffset.first, rotationOffset.second) * scale + positionOffset,
                           toMyVector3(vertex3.Position).rotate(rotationOffset.first, rotationOffset.second) * scale + positionOffset, material,
                           toMyVector3(vertex1.TextureCoordinate), toMyVector3(vertex2.TextureCoordinate), toMyVector3(vertex3.TextureCoordinate)};
//                std::cout << t.getUVAt({1, -1, 1}) << std::endl;

//                std::cout << Triangle{toMyVector3(vertex1.Position), toMyVector3(vertex2.Position), toMyVector3(vertex3.Position)} << std::endl;


                //                std::cout << t->getMaterial()->getAlbedoAt({0.5, 0.5, 0}) << std::endl;
//                std::cout << toMyVector3(vertex1.TextureCoordinate) << toMyVector3(vertex2.TextureCoordinate) << toMyVector3(vertex3.TextureCoordinate) << std::endl;
                objects.push_back(std::make_unique<Triangle>(toMyVector3(vertex1.Position).rotate(rotationOffset.first, rotationOffset.second) * scale + positionOffset, toMyVector3(vertex2.Position).rotate(rotationOffset.first, rotationOffset.second) * scale + positionOffset,
                                                             toMyVector3(vertex3.Position).rotate(rotationOffset.first, rotationOffset.second) * scale + positionOffset, material,
                                                             toMyVector3(vertex1.TextureCoordinate), toMyVector3(vertex2.TextureCoordinate), toMyVector3(vertex3.TextureCoordinate)));

//            std::cout <<
//            std::cout << "T" << j / 3 << ": " << curMesh.Indices[j] << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
            }




//
//            Camera camera = {
//                    {0, -3, 2},
//                    {0, M_PI / 10},
//                    0.4,
//                    {1, 1,},
//                    {500, 500}
//            };

//            std::cout << objects.size() << std::endl;
//            std::cout << *objects[0]->getMaterial() << std::endl;

            return objects;
//            return std::make_unique<BVHNode>(objects);
//            return std::make_shared<Objects>(objects);
        }
        throw std::runtime_error("Lol nope");
    }
}
