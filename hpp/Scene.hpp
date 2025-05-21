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

class Scene {
    private:
        //alle generierten Dreieck-Objekte
        std::vector<Triangle> triangles;
        std::vector<Vertex> vertices;
        std::vector<RGBA> colors;

        
        Image transformHitpointsToImage(std::vector<std::vector<Hitpoint>> hitpoints);
        Image transformHitpointsToImage(std::vector<Hitpoint> hitpoints);
        //Berechnung der Schnittpunkte von Rays und Triangles
        std::vector<Hitpoint> calculateHitpoints(std::vector<Ray>& rays);    
        
        public:
        Camera camera; //eigentlich private, aber für Debugging sichtbar

        Scene(const std::string filePathObj, const std::string filePathMtl = "");

        //Bündelt calculateHitpoints und convertHitpointsToImage
        Image generateImage();
        
};