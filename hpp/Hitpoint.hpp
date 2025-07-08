#pragma once

#include "structs/Point3D.hpp"
#include "Triangle.hpp"

class Hitpoint {
    private:
    float t = std::numeric_limits<float>::max();
    Point3D position;
    Vector3D normal;
    float distance = std::numeric_limits<float>::max();
    const Triangle* triangle = nullptr;

    public:
    Hitpoint();
    Point3D getPosition();
    Vector3D getNormal();
    float getDistance();
    const Triangle* getTriangle() const;
    float getT() const;
    void setT(float newT);
    void setPosition(const Point3D& pos);
    void setNormal( const Vector3D& nor);
    void setDistance(float d);
    void setTriangle(const Triangle* tri);
};