#pragma once
#include <Eigen/Dense>
#include "Structs.hpp"
#include "Triangle.hpp"
#include "Hitpoint.hpp"
#include "Ray.hpp"
#include "Image.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "Loader.hpp"

/**
 * @brief Repräsentiert eine 3D-Szene mit Geometrie, Kamera, Beleuchtung und Render-Logik.
 * 
 * Die Scene-Klasse lädt ein OBJ-Modell, verwaltet Materialien und Dreiecke,
 * nutzt einen KD-Tree für schnelle Schnittpunktsuche und berechnet 
 * eine Bildausgabe mittels Raytracing.
 */
class Scene {
private:
    std::vector<Triangle> triangles;  ///< Alle geladenen Dreiecke
    std::vector<Vertex> vertices;     ///< Alle geladenen Vertices
    std::vector<Vector3D> normals;    ///< Alle geladenen Normalen
    std::vector<Material> materials;  ///< Materialien (diffus, ambient, spekular)

    Camera camera;                    ///< Kameraobjekt (für Ray-Generierung)
    KDTree* kdtree = nullptr;         ///< KD-Tree zur Beschleunigung der Strahlschnittberechnung

    /**
     * @brief Berechnet die Farbe eines Hitpoints basierend auf Material, Licht, etc.
     * 
     * @param hp Treffpunkt des Strahls.
     * @return Farbwert mit Beleuchtung.
     */
    RGBA computeShading(Hitpoint& hp);

    /**
     * @brief Wandelt eine Liste von Hitpoints in ein Bild um.
     * 
     * Führt Beleuchtungsberechnung durch und setzt pro Pixel die entsprechende Farbe.
     * 
     * @param hitpoints Liste mit Strahl-Treffpunkten.
     * @return Gerendertes Bild.
     */
    Image transformHitpointsToImage(std::vector<Hitpoint> hitpoints);

    /**
     * @brief Berechnet die Hitpoints für eine Liste von Strahlen.
     * 
     * Nutzt KD-Tree zur effizienten Berechnung.
     * 
     * @param rays Liste von Strahlen.
     * @return Liste von Hitpoints.
     */
    std::vector<Hitpoint> calculateHitpoints(std::vector<Ray>& rays);

public:
    Light light;  ///< Globale Lichtquelle

    /**
     * @brief Konstruktor der Szene.
     * 
     * Lädt das OBJ-Modell, extrahiert die Vertices, Dreiecke, Normalen und Materialien
     * und erstellt daraus einen KD-Tree zur Beschleunigung der Strahlverfolgung.
     * 
     * @param filePathObj Pfad zur OBJ-Datei.
     */
    Scene(const std::string filePathObj);

    /**
     * @brief Generiert das Bild durch Raytracing.
     * 
     * Berechnet alle Strahlen, findet deren Schnittpunkte
     * und wendet das Beleuchtungsmodell auf die Hitpoints an.
     * 
     * @return Gerendertes Bild.
     */
    Image generateImage();

    /**
     * @brief Setzt die Kamera mit exakten Parametern.
     * 
     * Erlaubt vollständige Kontrolle über Position, Blickrichtung und Auflösung.
     * 
     * @param eyePos Kameraursprung (Position des Auges).
     * @param viewDir Blickrichtung der Kamera.
     * @param pixelWidth Breite eines Pixels in Weltkoordinaten.
     * @param pixelHeight Höhe eines Pixels in Weltkoordinaten.
     * @param horizontalPixels Anzahl horizontaler Pixel.
     * @param verticalPixels Anzahl vertikaler Pixel.
     */
    void setCamera(const Point3D& eyePos, const Vector3D& viewDir, float pixelWidth, float pixelHeight, int horizontalPixels, int verticalPixels);

    /**
     * @brief Vereinfachte Kamerakonfiguration per Skalierungs- und Auflösungsfaktor.
     * 
     * @param eyePos Kameraursprung.
     * @param viewDir Blickrichtung.
     * @param scalingFactor Skalierung des Sichtbereichs.
     * @param resolutionFactor Pixelanzahl pro Sichtwinkel.
     */
    void setCamera(const Point3D& eyePos, const Vector3D& viewDir, float scalingFactor, int resolutionFactor);
};
