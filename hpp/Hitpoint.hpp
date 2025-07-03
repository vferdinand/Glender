#pragma once

#include "structs/Point3D.hpp"
#include "Triangle.hpp"

class Hitpoint {
    private:
    float t = std::numeric_limits<float>::max();
    Point3D position;
    float distance = std::numeric_limits<float>::max();
    const Triangle* triangle = nullptr;
    float u = 0.0f;
    float v = 0.0f;

    public:
    Hitpoint();
    Point3D getPosition();
    float getDistance();
    const Triangle* getTriangle() const;
    float getT() const;

    void setT(float newT);
    void setPosition(const Point3D& pos);
    void setDistance(float d);
    void setTriangle(const Triangle* tri);
    float getU() const;
    void setU(float u);
    float getV() const;
    void setV(float v);
};