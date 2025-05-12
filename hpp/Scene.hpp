#pragma once
#include <vector>
#include "Triangle.hpp"
#include "Hitpoint.hpp"

class Scene {
    private:
        std::vector<Triangle> triangles;
        std::vector<Point3D> points;
    public:
        void addTriangle(Triangle tri);

        const std::vector<Triangle>& getTriangles() const;
};