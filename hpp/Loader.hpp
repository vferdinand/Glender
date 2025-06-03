#pragma once

#include "Structs.hpp"
#include "Triangle.hpp"
#include "Material.hpp"

#include <string>
#include <vector>

#include <fstream>
#include <sstream>
#include <iostream>

class Loader {
private:
    std::vector<Vertex> vertices;
    std::vector<Vector3D> verticesNormals;
    std::vector<Triangle> triangles;
    std::vector<RGBA> colors;
    std::vector<std::string> materialNames;
    std::vector<Material> materials;

    // Lädt Farben und Materialnamen aus einer .mtl-Datei
    bool initializeColor(const std::string& filePathMTL);

    // Lädt Vertices, Normalen und Dreiecke aus einer .obj-Datei
    bool initializeVerticiesTriangles(const std::string& filePathOBJ);

    // Gibt Index eines Materials zurück, -1 wenn nicht gefunden
    int16_t locateMaterial(const std::string& material);

    // Lädt .obj-Datei
    void loadOBJ(const std::string& filePathOBJ);
    
public:
    // Standardkonstruktor
    Loader(const std::string& filePathOBJ);

    // Gibt Referenz auf geladene Vertices zurück
    const std::vector<Vertex>& getVertices() const;

    // Gibt Referenz auf geladene Dreiecke zurück
    const std::vector<Triangle>& getTriangles() const;

    // Gibt Referenz auf geladene Farben zurück
    const std::vector<RGBA>& getColors() const;
};