#pragma once

#include <iostream>

struct Vertex {
    float x, y, z;
};
typedef Vertex Vector3D;
typedef Vertex Point3D;


struct RGBA {
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    double a = 1.0;
};

// Overload the stream operator
inline std::ostream& operator<<(std::ostream& os, const RGBA& color) {
    os << color.r;
    return os;
}
