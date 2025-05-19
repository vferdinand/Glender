#pragma once
#include <vector>
#include "Triangle.hpp"
#include "Hitpoint.hpp"
#include "Image.hpp"
#include "Structs.hpp"

class Scene {
    private:
        std::vector<Triangle> triangles;
        std::vector<Point3D> points;
        std::vector<RGBA> colors;

        Image transformHitpointsToImage(std::vector<std::vector<Hitpoint>> hitpoints);
    public:
        void addTriangle(Triangle tri);

        const std::vector<Triangle>& getTriangles() const;
};