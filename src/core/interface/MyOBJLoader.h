#pragma once

#include <memory>

#include "../../../lib/obj-loader/OBJ_Loader.h"
#include "../engine/Scene.h"
#include "../common/MyVector3.h"
#include "../engine/SolidTexture.h"

namespace MyOBJLoader {
    MyVector3 toMyVector3(const objl::Vector3& shittyvector) {
        return {shittyvector.X, shittyvector.Y, shittyvector.Z};
    }

    MyVector3 toMyVector3(const objl::Vector2& shittyvector) {
        return {shittyvector.X, shittyvector.Y, 0};
    }

    const std::vector<SceneObject> readOBJ (const std::string& path) {
        objl::Loader loader;
        bool success = loader.LoadFile(path);
        if (!success) throw std::runtime_error("Couldn't read obj file!");

        for (int i = 0; i < loader.LoadedMeshes.size(); i++)
        {
            objl::Mesh curMesh = loader.LoadedMeshes[i];


            std::cout << "Mesh " << i << ": " << curMesh.MeshName << "\n";

            std::cout << curMesh.MeshMaterial.map_Kd << std::endl;

//            for (int j = 0; j < curMesh.Vertices.size(); j++)
//            {
//                objl::Vertex& vertex = curMesh.Vertices[j];
//                std::cout << "V" << j << ": " <<
//                          "Position: (" << vertex.Position.X << ", " << vertex.Position.Y << ", " << vertex.Position.Z << ") " <<
//                          "Normal: (" << vertex.Normal.X << ", " << vertex.Normal.Y << ", " << vertex.Normal.Z << ") " <<
//                          "Texture coordinate: (" << vertex.TextureCoordinate.X << ", " << vertex.TextureCoordinate.Y << ")\n";
//            }

            // Print Indices
//            std::cout << "Indices:\n";

            // Go through every 3rd index and print the
            //	triangle that these indices represent

            auto color = Material{std::make_shared<SolidTexture>(Intensity{1, 1, 1})};
//            auto color = Material{std::make_shared<ImageTexture>("../res/texture3.png")};
            std::vector<SceneObject> objects;

            for (int j = 0; j < curMesh.Indices.size(); j += 3) {
//                auto t1 = toMyVector3()

                double index1 = curMesh.Indices[j + 0];
                double index2 = curMesh.Indices[j + 1];
                double index3 = curMesh.Indices[j + 2];

                objl::Vertex& vertex1 = curMesh.Vertices[index1];
                objl::Vertex& vertex2 = curMesh.Vertices[index2];
                objl::Vertex& vertex3 = curMesh.Vertices[index3];

//                std::cout << Triangle{toMyVector3(vertex1.Position), toMyVector3(vertex2.Position), toMyVector3(vertex3.Position)} << std::endl;

                std::shared_ptr<Surface> t;
                t = std::make_shared<Triangle>(toMyVector3(vertex1.Position), toMyVector3(vertex2.Position), toMyVector3(vertex3.Position),
                                               toMyVector3(vertex1.TextureCoordinate), toMyVector3(vertex2.TextureCoordinate), toMyVector3(vertex3.TextureCoordinate));
                objects.emplace_back(t, color);

//            std::cout <<
//            std::cout << "T" << j / 3 << ": " << curMesh.Indices[j] << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
            }





            Camera camera = {
                    {0, -3, 2},
                    {0, M_PI / 10},
                    0.4,
                    {1, 1,},
                    {500, 500}
            };

            std::cout << objects.size() << std::endl;

            return objects;
        }
        throw std::runtime_error("Lol nope");
    }
}
