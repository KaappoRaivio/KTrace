#pragma once

#include <memory>

#include "lib/obj-loader/OBJ_Loader.h"
#include "Scene.h"
#include "MyVector3.h"
#include "SolidTexture.h"

namespace MyOBJLoader {
    MyVector3 toMyVector3(const objl::Vector3& shittyvector) {
        return {shittyvector.X, shittyvector.Y, shittyvector.Z};
    }

    Scene readOBJ (const std::string& path) {
        objl::Loader loader;
        bool success = loader.LoadFile("../res/untitled.obj");
        if (!success) throw std::runtime_error("Couldn't read obj file!");

        for (int i = 0; i < loader.LoadedMeshes.size(); i++)
        {
            objl::Mesh curMesh = loader.LoadedMeshes[i];


            std::cout << "Mesh " << i << ": " << curMesh.MeshName << "\n";

            // Print Vertices
            std::cout << "Vertices:\n";

            // Go through each vertex and print its number,
            //  position, normal, and texture coordinate
            for (int j = 0; j < curMesh.Vertices.size(); j++)
            {
                objl::Vertex& vertex = curMesh.Vertices[j];
                std::cout << "V" << j << ": " <<
                          "Position: (" << vertex.Position.X << ", " << vertex.Position.Y << ", " << vertex.Position.Z << ") " <<
                          "Normal: (" << vertex.Normal.X << ", " << vertex.Normal.Y << ", " << vertex.Normal.Z << ") " <<
                          "Texture coordinate: (" << vertex.TextureCoordinate.X << ", " << vertex.TextureCoordinate.Y << ")\n";
            }

            // Print Indices
            std::cout << "Indices:\n";

            // Go through every 3rd index and print the
            //	triangle that these indices represent

            auto color = Material{std::make_shared<SolidTexture>(Intensity{1, 1, 1})};
            std::vector<SceneObject> objects;

            for (int j = 0; j < curMesh.Indices.size(); j += 3) {
//                auto t1 = toMyVector3()

                double index1 = curMesh.Indices[j + 0];
                double index2 = curMesh.Indices[j + 1];
                double index3 = curMesh.Indices[j + 2];

                objl::Vertex& vertex1 = curMesh.Vertices[index1];
                objl::Vertex& vertex2 = curMesh.Vertices[index2];
                objl::Vertex& vertex3 = curMesh.Vertices[index3];

                std::cout << Triangle{toMyVector3(vertex1.Position), toMyVector3(vertex2.Position), toMyVector3(vertex3.Position)} << std::endl;

                std::shared_ptr<Surface> t;
                t = std::make_shared<Triangle>(toMyVector3(vertex1.Position), toMyVector3(vertex2.Position), toMyVector3(vertex3.Position));
                objects.emplace_back(t, color);

//            std::cout <<
//            std::cout << "T" << j / 3 << ": " << curMesh.Indices[j] << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
            }


            double radius = 0.2;
            std::vector<LightSource> lights = {
                    {{4,     4.5,  4},   Intensity{0.1, 0.1, 1} * 70, radius},
                    {{-4,    4.5,  5.5}, Intensity{1, 0.25, 1} * 30,  radius},
                    {{-0.12, 3.83, 3.9}, Intensity{1, 1, 0.25} * 1,   radius},
                    {{4,     -40,  40},  Intensity{1, 1, 1} * 800,    radius},
            };


            Camera camera = {
                    {0, -3, 2},
                    {0, M_PI / 10},
                    0.2,
                    {1, 1,},
                    {500, 500}
            };

            std::cout << objects.size() << std::endl;

            return {objects, lights, camera, 1, 1};
        }
        throw std::runtime_error("Lol nope");
    }
}
