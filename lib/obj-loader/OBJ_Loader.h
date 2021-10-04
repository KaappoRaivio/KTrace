

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>

#define OBJL_CONSOLE_OUTPUT

namespace objl {
    struct Vector2 {
        Vector2 () {
            X = 0.0f;
            Y = 0.0f;
        }

        Vector2 (float X_, float Y_) {
            X = X_;
            Y = Y_;
        }

        bool operator== (const Vector2& other) const {
            return (this->X == other.X && this->Y == other.Y);
        }

        bool operator!= (const Vector2& other) const {
            return !(this->X == other.X && this->Y == other.Y);
        }

        Vector2 operator+ (const Vector2& right) const {
            return Vector2(this->X + right.X, this->Y + right.Y);
        }

        Vector2 operator- (const Vector2& right) const {
            return Vector2(this->X - right.X, this->Y - right.Y);
        }

        Vector2 operator* (const float& other) const {
            return Vector2(this->X * other, this->Y * other);
        }


        float X;
        float Y;
    };


    struct Vector3 {

        Vector3 () {
            X = 0.0f;
            Y = 0.0f;
            Z = 0.0f;
        }

        Vector3 (float X_, float Y_, float Z_) {
            X = X_;
            Y = Y_;
            Z = Z_;
        }

        bool operator== (const Vector3& other) const {
            return (this->X == other.X && this->Y == other.Y && this->Z == other.Z);
        }

        bool operator!= (const Vector3& other) const {
            return !(this->X == other.X && this->Y == other.Y && this->Z == other.Z);
        }

        Vector3 operator+ (const Vector3& right) const {
            return Vector3(this->X + right.X, this->Y + right.Y, this->Z + right.Z);
        }

        Vector3 operator- (const Vector3& right) const {
            return Vector3(this->X - right.X, this->Y - right.Y, this->Z - right.Z);
        }

        Vector3 operator* (const float& other) const {
            return Vector3(this->X * other, this->Y * other, this->Z * other);
        }

        Vector3 operator/ (const float& other) const {
            return Vector3(this->X / other, this->Y / other, this->Z / other);
        }


        float X;
        float Y;
        float Z;
    };


    struct Vertex {
        Vector3 Position;
        Vector3 Normal;
        Vector2 TextureCoordinate;
    };

    struct Material {
        Material () {
            name;
            Ns = 0.0f;
            Ni = 0.0f;
            d = 0.0f;
            illum = 0;
        }


        std::string name;

        Vector3 Ka;

        Vector3 Kd;

        Vector3 Ks;

        float Ns;

        float Ni;

        float d;

        int illum;

        std::string map_Ka;

        std::string map_Kd;

        std::string map_Ks;

        std::string map_Ns;

        std::string map_d;

        std::string map_bump;
    };


    struct Mesh {

        Mesh () {

        }

        Mesh (std::vector<Vertex>& _Vertices, std::vector<unsigned int>& _Indices) {
            Vertices = _Vertices;
            Indices = _Indices;
        }

        std::string MeshName;

        std::vector<Vertex> Vertices;

        std::vector<unsigned int> Indices;


        Material MeshMaterial;
    };


    namespace math {

        Vector3 CrossV3 (const Vector3 a, const Vector3 b) {
            return Vector3(a.Y * b.Z - a.Z * b.Y,
                           a.Z * b.X - a.X * b.Z,
                           a.X * b.Y - a.Y * b.X);
        }


        float MagnitudeV3 (const Vector3 in) {
            return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
        }


        float DotV3 (const Vector3 a, const Vector3 b) {
            return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
        }


        float AngleBetweenV3 (const Vector3 a, const Vector3 b) {
            float angle = DotV3(a, b);
            angle /= (MagnitudeV3(a) * MagnitudeV3(b));
            return angle = acosf(angle);
        }


        Vector3 ProjV3 (const Vector3 a, const Vector3 b) {
            Vector3 bn = b / MagnitudeV3(b);
            return bn * DotV3(a, bn);
        }
    }


    namespace algorithm {

        Vector3 operator* (const float& left, const Vector3& right) {
            return Vector3(right.X * left, right.Y * left, right.Z * left);
        }


        bool SameSide (Vector3 p1, Vector3 p2, Vector3 a, Vector3 b) {
            Vector3 cp1 = math::CrossV3(b - a, p1 - a);
            Vector3 cp2 = math::CrossV3(b - a, p2 - a);

            if (math::DotV3(cp1, cp2) >= 0)
                return true;
            else
                return false;
        }


        Vector3 GenTriNormal (Vector3 t1, Vector3 t2, Vector3 t3) {
            Vector3 u = t2 - t1;
            Vector3 v = t3 - t1;

            Vector3 normal = math::CrossV3(u, v);

            return normal;
        }


        bool inTriangle (Vector3 point, Vector3 tri1, Vector3 tri2, Vector3 tri3) {

            bool within_tri_prisim = SameSide(point, tri1, tri2, tri3) && SameSide(point, tri2, tri1, tri3)
                                     && SameSide(point, tri3, tri1, tri2);


            if (!within_tri_prisim)
                return false;


            Vector3 n = GenTriNormal(tri1, tri2, tri3);


            Vector3 proj = math::ProjV3(point, n);


            if (math::MagnitudeV3(proj) == 0)
                return true;
            else
                return false;
        }


        inline void split (const std::string& in,
                           std::vector<std::string>& out,
                           std::string token) {
            out.clear();

            std::string temp;

            for (int i = 0; i < int(in.size()); i++) {
                std::string test = in.substr(i, token.size());

                if (test == token) {
                    if (!temp.empty()) {
                        out.push_back(temp);
                        temp.clear();
                        i += (int) token.size() - 1;
                    } else {
                        out.push_back("");
                    }
                } else if (i + token.size() >= in.size()) {
                    temp += in.substr(i, token.size());
                    out.push_back(temp);
                    break;
                } else {
                    temp += in[i];
                }
            }
        }


        inline std::string tail (const std::string& in) {
            size_t token_start = in.find_first_not_of(" \t");
            size_t space_start = in.find_first_of(" \t", token_start);
            size_t tail_start = in.find_first_not_of(" \t", space_start);
            size_t tail_end = in.find_last_not_of(" \t");
            if (tail_start != std::string::npos && tail_end != std::string::npos) {
                return in.substr(tail_start, tail_end - tail_start + 1);
            } else if (tail_start != std::string::npos) {
                return in.substr(tail_start);
            }
            return "";
        }


        inline std::string firstToken (const std::string& in) {
            if (!in.empty()) {
                size_t token_start = in.find_first_not_of(" \t");
                size_t token_end = in.find_first_of(" \t", token_start);
                if (token_start != std::string::npos && token_end != std::string::npos) {
                    return in.substr(token_start, token_end - token_start);
                } else if (token_start != std::string::npos) {
                    return in.substr(token_start);
                }
            }
            return "";
        }


        template<class T>
        inline const T& getElement (const std::vector<T>& elements, std::string& index) {
            int idx = std::stoi(index);
            if (idx < 0)
                idx = int(elements.size()) + idx;
            else
                idx--;
            return elements[idx];
        }
    }


    class Loader {
    public:

        Loader () {

        }

        ~Loader () {
            LoadedMeshes.clear();
        }


        bool LoadFile (std::string Path) {

            if (Path.substr(Path.size() - 4, 4) != ".obj")
                return false;


            std::ifstream file(Path);

            if (!file.is_open())
                return false;

            LoadedMeshes.clear();
            LoadedVertices.clear();
            LoadedIndices.clear();

            std::vector<Vector3> Positions;
            std::vector<Vector2> TCoords;
            std::vector<Vector3> Normals;

            std::vector<Vertex> Vertices;
            std::vector<unsigned int> Indices;

            std::vector<std::string> MeshMatNames;

            bool listening = false;
            std::string meshname;

            Mesh tempMesh;

#ifdef OBJL_CONSOLE_OUTPUT
            const unsigned int outputEveryNth = 1000;
            unsigned int outputIndicator = outputEveryNth;
#endif

            std::string curline;
            while (std::getline(file, curline)) {
#ifdef OBJL_CONSOLE_OUTPUT
                if ((outputIndicator = ((outputIndicator + 1) % outputEveryNth)) == 1) {
                    if (!meshname.empty()) {
                        std::cout
                                << "\r- " << meshname
                                << "\t| vertices > " << Positions.size()
                                << "\t| texcoords > " << TCoords.size()
                                << "\t| normals > " << Normals.size()
                                << "\t| triangles > " << (Vertices.size() / 3)
                                << (!MeshMatNames.empty() ? "\t| material: " + MeshMatNames.back() : "");
                    }
                }
#endif


                if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g" || curline[0] == 'g') {
                    if (!listening) {
                        listening = true;

                        if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g") {
                            meshname = algorithm::tail(curline);
                        } else {
                            meshname = "unnamed";
                        }
                    } else {


                        if (!Indices.empty() && !Vertices.empty()) {

                            tempMesh = Mesh(Vertices, Indices);
                            tempMesh.MeshName = meshname;


                            LoadedMeshes.push_back(tempMesh);


                            Vertices.clear();
                            Indices.clear();
                            meshname.clear();

                            meshname = algorithm::tail(curline);
                        } else {
                            if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g") {
                                meshname = algorithm::tail(curline);
                            } else {
                                meshname = "unnamed";
                            }
                        }
                    }
#ifdef OBJL_CONSOLE_OUTPUT
                    std::cout << std::endl;
                    outputIndicator = 0;
#endif
                }

                if (algorithm::firstToken(curline) == "v") {
                    std::vector<std::string> spos;
                    Vector3 vpos;
                    algorithm::split(algorithm::tail(curline), spos, " ");

                    vpos.X = std::stof(spos[0]);
                    vpos.Y = std::stof(spos[1]);
                    vpos.Z = std::stof(spos[2]);

                    Positions.push_back(vpos);
                }

                if (algorithm::firstToken(curline) == "vt") {
                    std::vector<std::string> stex;
                    Vector2 vtex;
                    algorithm::split(algorithm::tail(curline), stex, " ");

                    vtex.X = std::stof(stex[0]);
                    vtex.Y = std::stof(stex[1]);

                    TCoords.push_back(vtex);
                }

                if (algorithm::firstToken(curline) == "vn") {
                    std::vector<std::string> snor;
                    Vector3 vnor;
                    algorithm::split(algorithm::tail(curline), snor, " ");

                    vnor.X = std::stof(snor[0]);
                    vnor.Y = std::stof(snor[1]);
                    vnor.Z = std::stof(snor[2]);

                    Normals.push_back(vnor);
                }

                if (algorithm::firstToken(curline) == "f") {

                    std::vector<Vertex> vVerts;
                    GenVerticesFromRawOBJ(vVerts, Positions, TCoords, Normals, curline);


                    for (int i = 0; i < int(vVerts.size()); i++) {
                        Vertices.push_back(vVerts[i]);

                        LoadedVertices.push_back(vVerts[i]);
                    }

                    std::vector<unsigned int> iIndices;

                    VertexTriangluation(iIndices, vVerts);


                    for (int i = 0; i < int(iIndices.size()); i++) {
                        unsigned int indnum = (unsigned int) ((Vertices.size()) - vVerts.size()) + iIndices[i];
                        Indices.push_back(indnum);

                        indnum = (unsigned int) ((LoadedVertices.size()) - vVerts.size()) + iIndices[i];
                        LoadedIndices.push_back(indnum);

                    }
                }

                if (algorithm::firstToken(curline) == "usemtl") {
                    MeshMatNames.push_back(algorithm::tail(curline));


                    if (!Indices.empty() && !Vertices.empty()) {

                        tempMesh = Mesh(Vertices, Indices);
                        tempMesh.MeshName = meshname;
                        int i = 2;
                        while (1) {
                            tempMesh.MeshName = meshname + "_" + std::to_string(i);

                            for (auto& m: LoadedMeshes)
                                if (m.MeshName == tempMesh.MeshName)
                                    continue;
                            break;
                        }


                        LoadedMeshes.push_back(tempMesh);


                        Vertices.clear();
                        Indices.clear();
                    }

#ifdef OBJL_CONSOLE_OUTPUT
                    outputIndicator = 0;
#endif
                }

                if (algorithm::firstToken(curline) == "mtllib") {


                    std::vector<std::string> temp;
                    algorithm::split(Path, temp, "/");

                    std::string pathtomat = "";

                    if (temp.size() != 1) {
                        for (int i = 0; i < temp.size() - 1; i++) {
                            pathtomat += temp[i] + "/";
                        }
                    }


                    pathtomat += algorithm::tail(curline);

#ifdef OBJL_CONSOLE_OUTPUT
                    std::cout << std::endl << "- find materials in: " << pathtomat << std::endl;
#endif


                    LoadMaterials(pathtomat);
                }
            }

#ifdef OBJL_CONSOLE_OUTPUT
            std::cout << std::endl;
#endif


            if (!Indices.empty() && !Vertices.empty()) {

                tempMesh = Mesh(Vertices, Indices);
                tempMesh.MeshName = meshname;


                LoadedMeshes.push_back(tempMesh);
            }

            file.close();


            for (int i = 0; i < MeshMatNames.size(); i++) {
                std::string matname = MeshMatNames[i];


                for (int j = 0; j < LoadedMaterials.size(); j++) {
                    if (LoadedMaterials[j].name == matname) {
                        LoadedMeshes[i].MeshMaterial = LoadedMaterials[j];
                        break;
                    }
                }
            }

            if (LoadedMeshes.empty() && LoadedVertices.empty() && LoadedIndices.empty()) {
                return false;
            } else {
                return true;
            }
        }


        std::vector<Mesh> LoadedMeshes;

        std::vector<Vertex> LoadedVertices;

        std::vector<unsigned int> LoadedIndices;

        std::vector<Material> LoadedMaterials;

    private:


        void GenVerticesFromRawOBJ (std::vector<Vertex>& oVerts,
                                    const std::vector<Vector3>& iPositions,
                                    const std::vector<Vector2>& iTCoords,
                                    const std::vector<Vector3>& iNormals,
                                    std::string icurline) {
            std::vector<std::string> sface, svert;
            Vertex vVert;
            algorithm::split(algorithm::tail(icurline), sface, " ");

            bool noNormal = false;


            for (int i = 0; i < int(sface.size()); i++) {

                int vtype;

                algorithm::split(sface[i], svert, "/");


                if (svert.size() == 1) {

                    vtype = 1;
                }


                if (svert.size() == 2) {

                    vtype = 2;
                }


                if (svert.size() == 3) {
                    if (svert[1] != "") {

                        vtype = 4;
                    } else {

                        vtype = 3;
                    }
                }


                switch (vtype) {
                    case 1: {
                        vVert.Position = algorithm::getElement(iPositions, svert[0]);
                        vVert.TextureCoordinate = Vector2(0, 0);
                        noNormal = true;
                        oVerts.push_back(vVert);
                        break;
                    }
                    case 2: {
                        vVert.Position = algorithm::getElement(iPositions, svert[0]);
                        vVert.TextureCoordinate = algorithm::getElement(iTCoords, svert[1]);
                        noNormal = true;
                        oVerts.push_back(vVert);
                        break;
                    }
                    case 3: {
                        vVert.Position = algorithm::getElement(iPositions, svert[0]);
                        vVert.TextureCoordinate = Vector2(0, 0);
                        vVert.Normal = algorithm::getElement(iNormals, svert[2]);
                        oVerts.push_back(vVert);
                        break;
                    }
                    case 4: {
                        vVert.Position = algorithm::getElement(iPositions, svert[0]);
                        vVert.TextureCoordinate = algorithm::getElement(iTCoords, svert[1]);
                        vVert.Normal = algorithm::getElement(iNormals, svert[2]);
                        oVerts.push_back(vVert);
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }


            if (noNormal) {
                Vector3 A = oVerts[0].Position - oVerts[1].Position;
                Vector3 B = oVerts[2].Position - oVerts[1].Position;

                Vector3 normal = math::CrossV3(A, B);

                for (int i = 0; i < int(oVerts.size()); i++) {
                    oVerts[i].Normal = normal;
                }
            }
        }


        void VertexTriangluation (std::vector<unsigned int>& oIndices,
                                  const std::vector<Vertex>& iVerts) {


            if (iVerts.size() < 3) {
                return;
            }

            if (iVerts.size() == 3) {
                oIndices.push_back(0);
                oIndices.push_back(1);
                oIndices.push_back(2);
                return;
            }


            std::vector<Vertex> tVerts = iVerts;

            while (true) {

                for (int i = 0; i < int(tVerts.size()); i++) {

                    Vertex pPrev;
                    if (i == 0) {
                        pPrev = tVerts[tVerts.size() - 1];
                    } else {
                        pPrev = tVerts[i - 1];
                    }


                    Vertex pCur = tVerts[i];


                    Vertex pNext;
                    if (i == tVerts.size() - 1) {
                        pNext = tVerts[0];
                    } else {
                        pNext = tVerts[i + 1];
                    }


                    if (tVerts.size() == 3) {

                        for (int j = 0; j < int(tVerts.size()); j++) {
                            if (iVerts[j].Position == pCur.Position)
                                oIndices.push_back(j);
                            if (iVerts[j].Position == pPrev.Position)
                                oIndices.push_back(j);
                            if (iVerts[j].Position == pNext.Position)
                                oIndices.push_back(j);
                        }

                        tVerts.clear();
                        break;
                    }
                    if (tVerts.size() == 4) {

                        for (int j = 0; j < int(iVerts.size()); j++) {
                            if (iVerts[j].Position == pCur.Position)
                                oIndices.push_back(j);
                            if (iVerts[j].Position == pPrev.Position)
                                oIndices.push_back(j);
                            if (iVerts[j].Position == pNext.Position)
                                oIndices.push_back(j);
                        }

                        Vector3 tempVec;
                        for (int j = 0; j < int(tVerts.size()); j++) {
                            if (tVerts[j].Position != pCur.Position
                                && tVerts[j].Position != pPrev.Position
                                && tVerts[j].Position != pNext.Position) {
                                tempVec = tVerts[j].Position;
                                break;
                            }
                        }


                        for (int j = 0; j < int(iVerts.size()); j++) {
                            if (iVerts[j].Position == pPrev.Position)
                                oIndices.push_back(j);
                            if (iVerts[j].Position == pNext.Position)
                                oIndices.push_back(j);
                            if (iVerts[j].Position == tempVec)
                                oIndices.push_back(j);
                        }

                        tVerts.clear();
                        break;
                    }


                    float angle = math::AngleBetweenV3(pPrev.Position - pCur.Position, pNext.Position - pCur.Position) * (180 / 3.14159265359);
                    if (angle <= 0 && angle >= 180)
                        continue;


                    bool inTri = false;
                    for (int j = 0; j < int(iVerts.size()); j++) {
                        if (algorithm::inTriangle(iVerts[j].Position, pPrev.Position, pCur.Position, pNext.Position)
                            && iVerts[j].Position != pPrev.Position
                            && iVerts[j].Position != pCur.Position
                            && iVerts[j].Position != pNext.Position) {
                            inTri = true;
                            break;
                        }
                    }
                    if (inTri)
                        continue;


                    for (int j = 0; j < int(iVerts.size()); j++) {
                        if (iVerts[j].Position == pCur.Position)
                            oIndices.push_back(j);
                        if (iVerts[j].Position == pPrev.Position)
                            oIndices.push_back(j);
                        if (iVerts[j].Position == pNext.Position)
                            oIndices.push_back(j);
                    }


                    for (int j = 0; j < int(tVerts.size()); j++) {
                        if (tVerts[j].Position == pCur.Position) {
                            tVerts.erase(tVerts.begin() + j);
                            break;
                        }
                    }


                    i = -1;
                }


                if (oIndices.size() == 0)
                    break;


                if (tVerts.size() == 0)
                    break;
            }
        }


        bool LoadMaterials (std::string path) {

            if (path.substr(path.size() - 4, path.size()) != ".mtl")
                return false;

            std::ifstream file(path);


            if (!file.is_open())
                return false;

            Material tempMaterial;

            bool listening = false;


            std::string curline;
            while (std::getline(file, curline)) {

                if (algorithm::firstToken(curline) == "newmtl") {
                    if (!listening) {
                        listening = true;

                        if (curline.size() > 7) {
                            tempMaterial.name = algorithm::tail(curline);
                        } else {
                            tempMaterial.name = "none";
                        }
                    } else {


                        LoadedMaterials.push_back(tempMaterial);


                        tempMaterial = Material();

                        if (curline.size() > 7) {
                            tempMaterial.name = algorithm::tail(curline);
                        } else {
                            tempMaterial.name = "none";
                        }
                    }
                }

                if (algorithm::firstToken(curline) == "Ka") {
                    std::vector<std::string> temp;
                    algorithm::split(algorithm::tail(curline), temp, " ");

                    if (temp.size() != 3)
                        continue;

                    tempMaterial.Ka.X = std::stof(temp[0]);
                    tempMaterial.Ka.Y = std::stof(temp[1]);
                    tempMaterial.Ka.Z = std::stof(temp[2]);
                }

                if (algorithm::firstToken(curline) == "Kd") {
                    std::vector<std::string> temp;
                    algorithm::split(algorithm::tail(curline), temp, " ");

                    if (temp.size() != 3)
                        continue;

                    tempMaterial.Kd.X = std::stof(temp[0]);
                    tempMaterial.Kd.Y = std::stof(temp[1]);
                    tempMaterial.Kd.Z = std::stof(temp[2]);
                }

                if (algorithm::firstToken(curline) == "Ks") {
                    std::vector<std::string> temp;
                    algorithm::split(algorithm::tail(curline), temp, " ");

                    if (temp.size() != 3)
                        continue;

                    tempMaterial.Ks.X = std::stof(temp[0]);
                    tempMaterial.Ks.Y = std::stof(temp[1]);
                    tempMaterial.Ks.Z = std::stof(temp[2]);
                }

                if (algorithm::firstToken(curline) == "Ns") {
                    tempMaterial.Ns = std::stof(algorithm::tail(curline));
                }

                if (algorithm::firstToken(curline) == "Ni") {
                    tempMaterial.Ni = std::stof(algorithm::tail(curline));
                }

                if (algorithm::firstToken(curline) == "d") {
                    tempMaterial.d = std::stof(algorithm::tail(curline));
                }

                if (algorithm::firstToken(curline) == "illum") {
                    tempMaterial.illum = std::stoi(algorithm::tail(curline));
                }

                if (algorithm::firstToken(curline) == "map_Ka") {
                    tempMaterial.map_Ka = algorithm::tail(curline);
                }

                if (algorithm::firstToken(curline) == "map_Kd") {
                    tempMaterial.map_Kd = algorithm::tail(curline);
                }

                if (algorithm::firstToken(curline) == "map_Ks") {
                    tempMaterial.map_Ks = algorithm::tail(curline);
                }

                if (algorithm::firstToken(curline) == "map_Ns") {
                    tempMaterial.map_Ns = algorithm::tail(curline);
                }

                if (algorithm::firstToken(curline) == "map_d") {
                    tempMaterial.map_d = algorithm::tail(curline);
                }

                if (algorithm::firstToken(curline) == "map_Bump" || algorithm::firstToken(curline) == "map_bump" || algorithm::firstToken(curline) == "bump") {
                    tempMaterial.map_bump = algorithm::tail(curline);
                }
            }


            LoadedMaterials.push_back(tempMaterial);


            if (LoadedMaterials.empty())
                return false;

            else
                return true;
        }
    };
}
