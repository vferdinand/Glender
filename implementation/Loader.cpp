#include "../hpp/Loader.hpp"
#include "../hpp/KDTree.hpp"

// Konstruktor der Loader-Klasse.
// Dient zur Initialisierung eines Loader-Objekts.
// Momentan wird keine spezielle Initialisierung vorgenommen.
Loader::Loader(){}


/* /////////////////////////////////////////////////////////
 * Ist die Hauptfunktion zum Laden von .obj-Dateien.
 * /////////////////////////////////////////////////////////
 * 
 * Lädt eine .obj-Datei und optional eine zugehörige .mtl-Datei.
 * Wenn ein Materialpfad angegeben ist, werden zuerst die Farben geladen.
 * Danach erfolgt das Parsen der Geometrie.
 */
bool Loader::loadOBJ(const std::string& filePathOBJ, const std::string& filePathMTL) {
    if(filePathMTL != ""){
        initializeColor(filePathMTL);
    }
    return initializeVerticiesTriangles(filePathOBJ);
}

/*
 * Lädt Farbwerte und Materialnamen aus einer .mtl-Datei.
 * Unterstützt nur die diffuse Farbe (Kd) und Materialnamen (newmtl).
 * Fügt die Farben in die colors-Liste und die Namen in materialNames ein.
 * Der erste Eintrag ist ein Standardmaterial (weiß, ohne Namen),
 * um ein fallback-Material zu haben, falls kein "usemtl" angegeben ist.
 */
bool Loader::initializeColor(const std::string& filePathMTL){
    std::ifstream fileMTL(filePathMTL);
    if (!fileMTL.is_open()) {
        std::cerr << "Dummkopf Failed to open .mtl file: " << filePathMTL << std::endl;
        return false;
    }

    colors.push_back({1.0,1.0,1.0,1.0});
    materialNames.push_back("");

    std::string line;
    while (std::getline(fileMTL, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;        
        if (prefix == "newmtl") {
            std::string name;
            iss >> name;
            materialNames.push_back(name);
        }else if (prefix == "Kd"){
            RGBA color;
            iss >> color.r >> color.g >> color.b;
            colors.push_back(color);
        }
    }
    fileMTL.close();
    return true;
}

/*
 * Lädt Geometriedaten (Vertices, Normalen, Dreiecke) aus einer .obj-Datei.
 * Unterstützt:
 *  - Vertex-Positionen ("v")
 *  - Vertex-Normalen ("vn")
 *  - Flächen ("f") mit Dreiecksbeschränkung
 *  - Materialzuweisung ("usemtl")
 * Die Dreiecke werden in der Reihenfolge ihres Auftretens gespeichert,
 * inklusive Materialindex zur späteren Farbanwendung.
 */
bool Loader::initializeVerticiesTriangles(const std::string& filePathOBJ){
    std::ifstream fileOBJ(filePathOBJ);
    if (!fileOBJ.is_open()) {
        std::cerr << "Dummkopf Failed to open .obj file: " << filePathOBJ << std::endl;
        return false;
    }
    
    std::string line;
    u_int16_t materialIndex = 0;
    while (std::getline(fileOBJ, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        if (prefix == "vn") {
            Vector3D v;
            iss >> v.x >> v.y >> v.z;
            verticesNormals.push_back(v);
        }else if (prefix == "v") {
            Vertex v;
            iss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        } else if (prefix == "f") {
            std::array<uint32_t, 3> indices;
            std::string vertexStr;

            for (int i = 0; i < 3; ++i) {
                iss >> vertexStr;

                size_t slashPos = vertexStr.find('/');
                std::string indexStr;
                if (slashPos == std::string::npos) {
                    indexStr = vertexStr;
                } else {
                    indexStr = vertexStr.substr(0, slashPos);
                }

                indices[i] = std::stoi(indexStr) - 1;
            }

            triangles.push_back(Triangle({indices[0], indices[1], indices[2]}, materialIndex));
        } else if (prefix == "usemtl"){
            std::string newMaterial;
            iss >> newMaterial;
            if (locateMaterial(newMaterial) != -1){
                materialIndex = locateMaterial(newMaterial);
            }
        }
    }

    fileOBJ.close();
    return true;
}

void Loader::buildKDTreeAndIntersect(const Ray& ray) {
    KDTree* kdtree = new KDTree(triangles, vertices);  // greift auf Membervariablen zu

    Hitpoint hit;
    if (kdtree->intersect(ray, hit)) {
        // Treffer behandeln
        std::cout << "Treffer bei t=" << hit.getT() << std::endl;
    } else {
        std::cout << "Kein Treffer." << std::endl;
    }

    delete kdtree;
}

/*
 * Sucht einen Materialnamen in der Liste materialNames.
 * Gibt den Index zurück, falls gefunden, sonst -1.
 */
int16_t Loader::locateMaterial(const std::string& material) {
    for (size_t i = 0; i < materialNames.size(); ++i) {
        if (materialNames[i] == material)
            return static_cast<int16_t>(i);
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

// Gibt eine Referenz auf die geladenen Farben (aus .mtl) zurück.
const std::vector<RGBA>& Loader::getColors() const {
    return colors;
}
