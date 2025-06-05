#pragma once

#include "Structs.hpp"
#include "Triangle.hpp"
#include "Ray.hpp"
#include "Material.hpp"

#include <string>
#include <vector>

#include <fstream>
#include <sstream>
#include <iostream>

class Loader {
private:
    std::vector<Vertex> vertices;
    std::vector<Vector3D> normals;
    std::vector<Triangle> triangles;
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

    void buildKDTreeAndIntersect(const Ray& ray);

    // Gibt Referenz auf geladene Normalen zurück
    const std::vector<Vector3D>& getNormals() const;

    // Gibt Referenz auf geladene Materialien zurück
    const std::vector<Material>& getMaterials() const;
};
