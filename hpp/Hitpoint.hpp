#ifndef HITPOINT_H
#define HITPOINT_H

#include "Structs.hpp"
#include "Triangle.hpp"
#include <limits>

class Hitpoint {
    private:
    Point3D position;
    float distance = std::numeric_limits<float>::max();
    const Triangle* triangle = nullptr;

    public:
    const Point3D getPosition();
    const float getDistance();
    const Triangle* getTriangle();
};

#endif