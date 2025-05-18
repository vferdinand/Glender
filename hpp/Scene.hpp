#pragma once
#include <vector>
#include <Eigen/Dense>
#include "Triangle.hpp"
#include "Hitpoint.hpp"
#include "Image.hpp"
#include "Camera.hpp"


class Scene {
    private:
        //alle generierten Dreieck-Objekte
        std::vector<Triangle> triangles;
        std::vector<Point3D> points;
    public:
        //Dreieck hinzufügen zur Scene
        void addTriangle(Triangle tri);
        //Bündelt calculateHitpoints und convertHitpointsToImage
        Image generateImage();
        //Berechnung der Schnittpunkte von Rays und Triangles
        std::vector<Hitpoint> calculateHitpoints(std::vector<Ray>& rays,std::vector<Triangle>& triangles, std::vector<Vertex>& vertices);
        //Farbe der Dreiecke Pixeln zuweisen
        Image convertHitpointsToImage(std::vector<Hitpoint> hitpoints);
        //getter für Dreieck-Vektor
        const std::vector<Triangle>& getTriangles() const;
};