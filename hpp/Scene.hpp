#pragma once
#include <vector>
#include <Eigen/Dense>
#include "Triangle.hpp"
#include "Hitpoint.hpp"
#include "Image.hpp"
#include "Structs.hpp"
#include "Ray.hpp"
#include "Camera.hpp"

class Scene {
    private:
        //alle generierten Dreieck-Objekte
        const std::vector<Triangle> triangles;
        const std::vector<Vertex> vertices;
        std::vector<RGBA> colors;

        Image transformHitpointsToImage(std::vector<std::vector<Hitpoint>> hitpoints);
        Image transformHitpointsToImage(std::vector<Hitpoint> hitpoints, size_t height, size_t width);
        //Berechnung der Schnittpunkte von Rays und Triangles
        std::vector<std::vector<Hitpoint>> calculateHitpoints(const std::vector<std::vector<Ray>>& rays);
        //Farbe der Dreiecke Pixeln zuweisen
        const std::vector<Triangle>& getTriangles() const;
        
        public:
        //Bündelt calculateHitpoints und convertHitpointsToImage
        Image generateImage();
        
};