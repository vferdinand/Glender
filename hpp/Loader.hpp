#pragma once

#include "Ray.hpp"
#include "Material.hpp"
#include "KDTree.hpp"
#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
#include <sstream>

class Loader {
private:
    std::vector<Vertex> vertices;
    std::vector<Vector3D> normals;
    std::vector<Triangle> triangles;
    std::vector<Material> materials;
    std::vector<Vector3D> texture_coord;
    std::vector<std::string> textures;
    
    /**
     * @brief Lädt Farben und Materialeigenschaften aus einer .mtl-Datei.
     * 
     * Unterstützt Kd (diffuse Farbe), Ka (ambient), Ks (specular), Ns (Glanz), d/Tr (Transparenz), illum.
     * 
     * @param filePathMTL Pfad zur Material-Datei (.mtl).
     * @return true, wenn erfolgreich geladen; andernfalls false.
     */
    bool initializeColor(const std::string& filePathMTL);

    
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
    bool initializeVerticiesTriangles(const std::string& filePathOBJ);

    /**
     * @brief Sucht nach einem Materialnamen in der geladenen Liste.
     * 
     * @param material Name des gesuchten Materials.
     * @return Index des Materials oder -1, falls nicht gefunden.
     */
    int16_t locateMaterial(const std::string& material);

    /**
     * @brief Hauptfunktion zum Laden einer .obj-Datei.
     * 
     * Diese Methode lädt eine .obj-Datei sowie ggf. eine verlinkte .mtl-Datei für Materialien.
     * Danach erfolgt das Parsen der Geometrie.
     * 
     * @param filePathOBJ Pfad zur .obj-Datei.
     */
    void loadOBJ(const std::string& filePathOBJ);
    
public:
    
    /**
     * @brief Konstruktor der Loader-Klasse.
     * 
     * Lädt beim Erstellen automatisch die übergebene .obj-Datei.
     * 
     * @param filePathOBJ Pfad zur zu ladenden .obj-Datei (relativ zu "obj/").
     */
    Loader(const std::string& filePathOBJ);

    // Gibt Referenz auf geladene Vertices zurück
    const std::vector<Vertex>& getVertices() const;

    // Gibt Referenz auf geladene Dreiecke zurück
    const std::vector<Triangle>& getTriangles() const;

    // Gibt Referenz auf geladene Farben zurück
    const std::vector<RGBA>& getColors() const;

    /**
     * @brief Erstellt einen KD-Baum aus den geladenen Dreiecken und testet Ray-Intersection.
     * 
     * @param ray Der zu testende Strahl.
     */
    void buildKDTreeAndIntersect(const Ray& ray);

    // Gibt Referenz auf geladene Normalen zurück
    const std::vector<Vector3D>& getNormals() const;

    // Gibt Referenz auf geladene Materialien zurück
    const std::vector<Material>& getMaterials() const;
};
