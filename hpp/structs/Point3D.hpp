#pragma once

#include "Vector3D.hpp"

struct Point3D;

/**
 * @struct Point3D
 * @brief Repräsentiert einen Punkt im 3D-Raum.
 */
struct Point3D {
    float x, y, z;

    Point3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    Point3D operator+(const Vector3D& vec) const {
        return {x + vec.x, y + vec.y, z + vec.z};
    }

    Vector3D operator-(const Point3D& p) const {
        return {x - p.x, y - p.y, z - p.z};
    }
};
