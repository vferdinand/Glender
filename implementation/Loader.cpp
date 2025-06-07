#include "../hpp/Loader.hpp"

/**
 * @brief Konstruktor der Loader-Klasse.
 * 
 * Lädt beim Erstellen automatisch die übergebene .obj-Datei.
 * 
 * @param filePathOBJ Pfad zur zu ladenden .obj-Datei (relativ zu "obj/").
 */
Loader::Loader(const std::string& filePathOBJ){
    loadOBJ(filePathOBJ);
}


/**
 * @brief Hauptfunktion zum Laden einer .obj-Datei.
 * 
 * Diese Methode lädt eine .obj-Datei sowie ggf. eine verlinkte .mtl-Datei für Materialien.
 * Danach erfolgt das Parsen der Geometrie.
 * 
 * @param filePathOBJ Pfad zur .obj-Datei.
 */
void Loader::loadOBJ(const std::string& filePathOBJ){
    std::ifstream fileOBJ("obj/" + filePathOBJ);
    if (!fileOBJ.is_open()) {
        std::cerr << "Dummkopf Failed to open .obj file: " << filePathOBJ << std::endl;
        return;
    }
    
    std::string line;
    materials.push_back(Material("",{1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}));
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

/**
 * @brief Lädt Farben und Materialeigenschaften aus einer .mtl-Datei.
 * 
 * Unterstützt Kd (diffuse Farbe), Ka (ambient), Ks (specular), Ns (Glanz), d/Tr (Transparenz), illum.
 * 
 * @param filePathMTL Pfad zur Material-Datei (.mtl).
 * @return true, wenn erfolgreich geladen; andernfalls false.
 */
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
        }else if (prefix == "Ns") {
            float shininess;
            iss >> shininess;
            materials.back().setShininess(shininess);
        }else if (prefix == "d" || prefix == "Tr") {
            float dissolve;
            iss >> dissolve;
            materials.back().setDissolve(dissolve);
        }else if (prefix == "illum") {
            int8_t illum;
            iss >> illum;
            materials.back().setIllum(illum);
        }
    }
    fileMTL.close();
    return true;
}

/**
 * @brief Init Geometriedaten (Vertices, Normalen, Dreiecke) aus einer .obj-Datei.
 * 
 * Unterstützt:
 *  - Vertex-Positionen ("v")
 *  - Vertex-Normalen ("vn")
 *  - Flächen ("f") mit Dreiecksbeschränkung
 *  - Materialzuweisung ("usemtl")
 * Die Dreiecke werden in der Reihenfolge ihres Auftretens gespeichert,
 * inklusive Materialindex zur späteren Farbanwendung.
 * 
 * @param filePathOBJ Pfad zur .obj-Datei.
 * @return true, wenn erfolgreich geladen; andernfalls false.
 */
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

            std::string vertexToken;
            while (iss >> vertexToken) {
                size_t firstSlash  = vertexToken.find('/');
                size_t secondSlash = std::string::npos;

                uint32_t vIndex = 0;
                uint32_t nIndex = 0;

                if (firstSlash == std::string::npos) {
                    // format: "v"
                    vIndex = static_cast<uint32_t>(std::stoi(vertexToken)) - 1;
                    nIndex = 0;
                } else {
                    secondSlash = vertexToken.find('/', firstSlash + 1);
                    {
                        std::string vStr = vertexToken.substr(0, firstSlash);
                        vIndex = static_cast<uint32_t>(std::stoi(vStr)) - 1;
                    }
                    if (secondSlash == std::string::npos) {
                        // format: "v/vt"
                        nIndex = 0;
                    } else {
                        // format: "v//vn" or "v/vt/vn"
                        std::string vnStr = vertexToken.substr(secondSlash + 1);
                        if (!vnStr.empty()) {
                            try {
                                nIndex = static_cast<uint32_t>(std::stoi(vnStr)) - 1;
                            } catch (const std::invalid_argument&) {
                                std::cerr << "Warnung: Ungültiger Normalenindex in Zeile: " << line << std::endl;
                                nIndex = 0;
                            }
                        } else {
                            nIndex = 0;
                        }
                    }
                }

                faceVertexIdx.push_back(vIndex);
                faceNormalIdx.push_back(nIndex);
            }

            if (faceVertexIdx.size() < 3) {
                continue;
            }

            uint32_t normalIndexForAllTri = faceNormalIdx[0];

            // Fan‐triangulate: for N vertices, create (N−2) triangles:
            //   (0,1,2), (0,2,3), (0,3,4), ...
            for (size_t i = 1; i + 1 < faceVertexIdx.size(); ++i) {
                // Build a small vector of exactly 3 indices:
                std::vector<uint32_t> triVerts = {
                    faceVertexIdx[0],
                    faceVertexIdx[i],
                    faceVertexIdx[i + 1]
                };
                triangles.emplace_back(triVerts, normalIndexForAllTri, materialIndex);
            }
        }
        // ignore any other prefixes
    }
    std::cout << "Dummkopf Loaded " << vertices.size() << " vertices, "
              << normals.size() << " normals, "
              << triangles.size() << " triangles, "
              << materials.size() << " materials." << std::endl;
    fileOBJ.close();
    return true;
}

/**
 * @brief Erstellt einen KD-Baum aus den geladenen Dreiecken und testet Ray-Intersection.
 * 
 * @param ray Der zu testende Strahl.
 */
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

/**
 * @brief Sucht nach einem Materialnamen in der geladenen Liste.
 * 
 * @param material Name des gesuchten Materials.
 * @return Index des Materials oder -1, falls nicht gefunden.
 */
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
