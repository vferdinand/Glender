#include "../hpp/Loader.hpp"

// Konstruktor der Loader-Klasse.
// Dient zur Initialisierung eines Loader-Objekts.
// Momentan wird keine spezielle Initialisierung vorgenommen.
Loader::Loader(const std::string& filePathOBJ){
    loadOBJ(filePathOBJ);
}


/* /////////////////////////////////////////////////////////
 * Ist die Hauptfunktion zum Laden von .obj-Dateien.
 * /////////////////////////////////////////////////////////
 * 
 * Lädt eine .obj-Datei und optional eine zugehörige .mtl-Datei.
 * Wenn ein Materialpfad angegeben ist, werden zuerst die Farben geladen.
 * Danach erfolgt das Parsen der Geometrie.
 */
void Loader::loadOBJ(const std::string& filePathOBJ){
    std::ifstream fileOBJ(filePathOBJ);
    if (!fileOBJ.is_open()) {
        std::cerr << "Dummkopf Failed to open .obj file: " << filePathOBJ << std::endl;
        return;
    }
    
    std::string line;
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

    materials.push_back(Material("",{1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}, {1.0,1.0,1.0,1.0}));

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
        }else if (prefix == "Kd"){
            RGBA color;
            iss >> color.r >> color.g >> color.b;
            material.setDifuse(color);
        }else if (prefix == "Ka"){
            RGBA color;
            iss >> color.r >> color.g >> color.b;
            material.setAmbient(color);
        }else if (prefix == "Ks"){
            RGBA color;
            iss >> color.r >> color.g >> color.b;
            material.setSpecular(color);
        }else if (prefix == "Ns") {
            float shininess;
            iss >> shininess;
            material.setShininess(shininess);
        }else if (prefix == "d" || prefix == "Tr") {
            float dissolve;
            iss >> dissolve;
            material.setDissolve(dissolve);
        }else if (prefix == "illum") {
            int8_t illum;
            iss >> illum;
            material.setIllum(illum);
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
            normals.push_back(v);
        }else if (prefix == "v") {
            Vertex v;
            iss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        } else if (prefix == "f") {
            std::array<uint32_t, 3> vertexIndices;
            std::array<uint32_t, 3> normalIndices;

            for (int i = 0; i < 3; ++i) {
                std::string vertexStr;
                iss >> vertexStr;

                size_t firstSlash = vertexStr.find('/');
                size_t secondSlash = vertexStr.find('/', firstSlash + 1);

                // Vertex Index
                std::string vStr = vertexStr.substr(0, firstSlash);
                vertexIndices[i] = std::stoi(vStr) - 1;

                // Normal Index
                if (secondSlash != std::string::npos) {
                    std::string vnStr = vertexStr.substr(secondSlash + 1);
                    normalIndices[i] = std::stoi(vnStr) - 1;
                } else {
                    normalIndices[i] = 0; // oder Fehlerbehandlung
                }
            }
            
            uint32_t normalIndex = normalIndices[0];

            triangles.push_back(Triangle({vertexIndices[0], vertexIndices[1], vertexIndices[2]}, normalIndex, materialIndex));

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

/*
 * Sucht einen Materialnamen in der Liste materialNames.
 * Gibt den Index zurück, falls gefunden, sonst -1.
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

// Gibt eine Referenz auf die geladenen Materialien zurück.
const std::vector<Material>& Loader::getMaterials() const {
    return materials;
}