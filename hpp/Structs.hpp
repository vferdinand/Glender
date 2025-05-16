#pragma once
#include <cmath>

//forward declarations
struct Vertex;
struct Point3D;
struct Vector3D;


struct Vertex {
    float x, y, z;
};

struct Point3D {
    float x, y, z;

    Point3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
    
    // Point + Vector = Point
    Point3D operator+(const Vector3D& vec) const;
    
    // Point - Point = Vector
    Vector3D operator-(const Point3D& p) const;
};

struct Vector3D {
    float x, y, z;

    //Constructor
    Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : x(x), y(y), z(z) {}
     //Overload operators
    Vector3D operator+(const Vector3D& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }
    
    Vector3D operator-(const Vector3D& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    
    Vector3D operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }
    
    Vector3D operator/(float scalar) const {
        return {x / scalar, y / scalar, z / scalar};
    }    
};

inline Point3D Point3D::operator+(const Vector3D& vec) const {
    return {x + vec.x, y + vec.y, z + vec.z};
}

inline Vector3D Point3D::operator-(const Point3D& p) const {
    return {x - p.x, y - p.y, z - p.z};
}

// Vector + Point = Point (Commmutativity)
inline Point3D operator+(const Vector3D& vec, const Point3D& p) {
    return p + vec;
}

struct RGBA {
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    double a = 1.0;
};