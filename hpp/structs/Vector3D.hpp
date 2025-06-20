#pragma once
#include <cmath>

struct Vector3D;

/**
 * @struct Vector3D
 * @brief Repräsentiert einen 3D-Vektor.
 */
struct Vector3D {
    float x, y, z;

    Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : x(x), y(y), z(z) {} 

    /**
     * 
     * @brief Vektoraddition.
     * @param other Der andere Vektor
     * @return Ergebnis der Addition
     */
    Vector3D operator+(const Vector3D& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3D operator-() const {
    return {-x, -y, -z};
}   

    
    /**
     * @brief Vektorsubtraktion.
     * @param other Der andere Vektor
     * @return Ergebnis der Subtraktion
     */
    Vector3D operator-(const Vector3D& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    
    /**
     * @brief Skalarmultiplikation.
     * @param scalar Der Skalarwert
     * @return Ergebnis der Multiplikation
     */
    Vector3D operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }
    
    /**
     * @brief Skalardivision.
     * @param scalar Der Skalarwert
     * @return Ergebnis der Division
     */
    Vector3D operator/(float scalar) const {
        return {x / scalar, y / scalar, z / scalar};
    }    
    
    float dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3D normalized() const {
        float len = std::sqrt(dot(*this));
        return len > 0.0f ? (*this) / len : Vector3D(0, 0, 0);
    }

    Vector3D reflected(const Vector3D& normal) const {
        return (*this) - normal * (2.0f * this->dot(normal));
    }
};