#pragma once
#include <vector>
#include <Eigen/Dense>
#include "Triangle.hpp"
#include "Hitpoint.hpp"
#include "Image.hpp"
#include "Structs.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Loader.hpp"
#include "KDTree.hpp"
#include <chrono>

class Scene {
    private:
        //alle generierten Dreieck-Objekte
        std::vector<Triangle> triangles;
        std::vector<Vertex> vertices;
        std::vector<RGBA> colors;

        Camera camera; //eigentlich private, aber für Debugging sichtbar
        
        Image transformHitpointsToImage(std::vector<Hitpoint> hitpoints);
        //Berechnung der Schnittpunkte von Rays und Triangles
        std::vector<Hitpoint> calculateHitpoints(std::vector<Ray>& rays);    
        
        KDTree* kdtree = nullptr; // Zeiger auf KDTree
    public:
        //Kamera Konfiguration
        void setCamera(const Point3D& eyePos, const Vector3D& viewDir, float pixelWidth, float pixelHeight, int horizontalPixels, int verticalPixels);

        Scene(const std::string filePathObj, const std::string filePathMtl = "");

        //Bündelt calculateHitpoints und convertHitpointsToImage
        Image generateImage();

        std::vector<Hitpoint> calculateHitpointsBruteForce(std::vector<Ray>& rays);
        std::vector<Hitpoint> calculateHitpointsKDTree(std::vector<Ray>& rays);
        void benchmarkIntersection(); // Optional: Zeitvergleich ausgeben

        
};