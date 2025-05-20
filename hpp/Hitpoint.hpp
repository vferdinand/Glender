#pragma once

#include "Structs.hpp"
#include "Triangle.hpp"
#include <limits>

class Hitpoint {
    private:
    Point3D position;
    float distance = std::numeric_limits<float>::max();
    const Triangle* triangle = nullptr;

    public:
    Hitpoint();
    const Point3D getPosition();
    float getDistance();
    const Triangle* getTriangle();

    void setPosition(const Point3D& pos);
    void setDistance(float d);
    void setTriangle(const Triangle* tri);
};