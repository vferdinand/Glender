#include "../hpp/Loader.hpp"

Loader::Loader(const std::string& filePathOBJ){
    loadOBJ(filePathOBJ);
}

void Loader::loadOBJ(const std::string& filePathOBJ){
    std::ifstream fileOBJ("obj/" + filePathOBJ);
    if (!fileOBJ.is_open()) {
        std::cerr << "Dummkopf Failed to open .obj file: " << filePathOBJ << std::endl;
        return;
    }
    
    std::string line;
    materials.push_back(Material("default",{1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}));
    materials.back().setShininess(8.0f);
    materials.back().setDissolve(1.0f);
    materials.back().setIllum(2);
    while (std::getline(fileOBJ, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        if(prefix == "mtllib"){
            std::string filePathMTL = "";
            iss >> filePathMTL;
            if(filePathMTL != ""){
                if(!initializeColor(filePathMTL)){
                    fileOBJ.close();
                    return;
                }
                break;
            }
        }
    }
    fileOBJ.close();
    initializeVerticiesTriangles(filePathOBJ);
}

bool Loader::initializeColor(const std::string& filePathMTL){
    std::ifstream fileMTL("obj/" + filePathMTL);
    if (!fileMTL.is_open()) {
        std::cerr << "Dummkopf Failed to open .mtl file: " << filePathMTL << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(fileMTL, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        
        Material material("",{1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0});

        if (prefix == "newmtl") {
            std::string name;
            iss >> name;
            material.setName(name);
            materials.push_back(material);
        }else if (prefix == "Kd"){
            RGBA color;
            iss >> color.r >> color.g >> color.b;
            materials.back().setDifuse(color);
        }else if (prefix == "Ka"){
            RGBA color;
            iss >> color.r >> color.g >> color.b;
            materials.back().setAmbient(color);
        }else if (prefix == "Ks"){
            RGBA color;
            iss >> color.r >> color.g >> color.b;
            materials.back().setSpecular(color);
        }else if (prefix == "Kr") {
            float kr;
            iss >> kr;
            materials.back().setReflectionFactor(kr);
        }else if (prefix == "Kt") {
            float kt;
            iss >> kt;
            materials.back().setTransparency(kt);
        }else if (prefix == "Ns") {
            float shininess;
            iss >> shininess;
            materials.back().setShininess(shininess);
        }else if (prefix == "Ni") {
            float ni;
            iss >> ni;
            materials.back().setIOR(ni);
        }else if (prefix == "d" || prefix == "Tr") {
            float dissolve;
            iss >> dissolve;
            materials.back().setDissolve(dissolve);
        }else if (prefix == "illum") {
            int8_t illum;
            iss >> illum;
            materials.back().setIllum(illum);
        }else if (prefix == "map_Kd") {
            std::string tex;
            iss >> tex;
            textures.push_back(Texture("obj/" + tex));
            materials.back().setDiffuseTex(static_cast<u_int8_t>(textures.size() - 1));
        }
    }
    fileMTL.close();
    return true;
}

bool Loader::initializeVerticiesTriangles(const std::string& filePathOBJ) {
    std::ifstream fileOBJ("obj/" + filePathOBJ);
    if (!fileOBJ.is_open()) {
        std::cerr << "Dummkopf Failed to open .obj file: " << filePathOBJ << std::endl;
        return false;
    }
    
    std::string line;
    uint16_t materialIndex = 0;

    while (std::getline(fileOBJ, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "vn") {
            Vector3D v;
            iss >> v.x >> v.y >> v.z;
            normals.push_back(v);

        } else if (prefix == "vt") {
            Vector3D v;
            iss >> v.x >> v.y;
            v.z = 0.0f;
            texture_coord.push_back(v);

        } else if (prefix == "v") {
            Vertex v;
            iss >> v.x >> v.y >> v.z;
            vertices.push_back(v);

        } else if (prefix == "usemtl") {
            std::string newMaterial;
            iss >> newMaterial;
            int idx = locateMaterial(newMaterial);
            if (idx != -1) {
                materialIndex = static_cast<uint16_t>(idx);
            }

        } else if (prefix == "f") {
            // Collect all vertex‐indices (+ possible normal‐indices) on this line.
            std::vector<uint32_t> faceVertexIdx;
            std::vector<uint32_t> faceNormalIdx;
            std::vector<uint32_t> faceTexIdx;

            std::string vertexToken;
            while (iss >> vertexToken) {
                uint32_t vIndex = 0, vtIndex = 0, vnIndex = 0;

                size_t firstSlash  = vertexToken.find('/');
                size_t secondSlash = std::string::npos;

                if (firstSlash == std::string::npos) {          // "v"
                    vIndex = std::stoul(vertexToken) - 1;
                } else {
                    secondSlash = vertexToken.find('/', firstSlash + 1);
                    vIndex = std::stoul(vertexToken.substr(0, firstSlash)) - 1;

                    if (secondSlash == std::string::npos) {     // "v/vt"
                        vtIndex = std::stoul(vertexToken.substr(firstSlash + 1)) - 1;
                    } else {
                        if (secondSlash > firstSlash + 1) {     // "v/vt/vn"
                            vtIndex = std::stoul(vertexToken.substr(firstSlash + 1,
                                        secondSlash - firstSlash - 1)) - 1;
                        }
                        // Rest kann "vn" oder leer sein ("v//vn")
                        std::string vnStr = vertexToken.substr(secondSlash + 1);
                        if (!vnStr.empty()) vnIndex = std::stoul(vnStr) - 1;
                    }
                }

                faceVertexIdx.push_back(vIndex);
                faceTexIdx.push_back(vtIndex);
                faceNormalIdx.push_back(vnIndex);
            }

            if (faceVertexIdx.size() < 3) {
                continue;
            }

            // Fan‐triangulate: for N vertices, create (N−2) triangles:
            //   (0,1,2), (0,2,3), (0,3,4), ...
            for (size_t i = 1; i + 1 < faceVertexIdx.size(); ++i) {
                // Build a small vector of exactly 3 indices:
                std::vector<uint32_t> triTex   = {          //  <‑‑ neu
                    faceTexIdx[0],
                    faceTexIdx[i],
                    faceTexIdx[i + 1]
                };
                std::vector<uint32_t> triVerts = {
                    faceVertexIdx[0],
                    faceVertexIdx[i],
                    faceVertexIdx[i + 1]
                };

                std::array<uint32_t, 3> triNormals = {
                    faceNormalIdx[0],
                    faceNormalIdx[i],
                    faceNormalIdx[i + 1]
                };

                triangles.emplace_back(triVerts, triNormals, materialIndex, triTex);
            }
        }
        // ignore any other prefixes
    }
    std::cout << "Dummkopf Loaded " << vertices.size() << " vertices, "
              << normals.size() << " normals, "
              << triangles.size() << " triangles, "
              << materials.size() << " materials." 
              << textures.size() << " textures."
                << " from " << filePathOBJ << "."
              << std::endl;
    fileOBJ.close();
    return true;
}

void Loader::buildKDTreeAndIntersect(const Ray& ray) {
    KDTree* kdtree = new KDTree(triangles, vertices);
    Hitpoint hit;
    if (kdtree->intersect(ray, hit)) {
        // Treffer behandeln
        std::cout << "Treffer bei t=" << hit.getT() << std::endl;
    } else {
        std::cout << "Kein Treffer." << std::endl;
    }

    delete kdtree;
}

int16_t Loader::locateMaterial(const std::string& material) {
    for (size_t i = 0; i < materials.size(); ++i) {
        if (materials[i].getName() == material) {
            return static_cast<int16_t>(i);
        }
    }
    return -1;
}

// Gibt eine Referenz auf die geladenen Vertices zurück.
const std::vector<Vertex>& Loader::getVertices() const {
    return vertices;
}

// Gibt eine Referenz auf die geladenen Dreiecke zurück.
const std::vector<Triangle>& Loader::getTriangles() const {
    return triangles;
}

// Gibt eine Referenz auf die geladenen Normalen zurück.
const std::vector<Vector3D>& Loader::getNormals() const {
    return normals;
}

// Gibt eine Referenz auf die geladenen Materialien zurück.
const std::vector<Material>& Loader::getMaterials() const {
    return materials;
}

// Gibt eine Referenz auf die geladenen Texturkoordinaten zurück.
const std::vector<Vector3D>& Loader::getTextureCoords() const {
    return texture_coord;
}  
// Gibt eine Referenz auf die geladenen Texturen zurück.
const std::vector<Texture>& Loader::getTextures() const {
    return textures;
}