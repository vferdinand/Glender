#pragma once
#include <cmath>
#include <iostream>

struct Vertex;
struct Point3D;
struct Vector3D;

/**
 * @struct Vertex
 * @brief Repräsentiert einen 3D-Vertex ohne spezielle Semantik.
 */
struct Vertex {
    float x, y, z;
};

/**
 * @struct Point3D
 * @brief Repräsentiert einen Punkt im 3D-Raum.
 */
struct Point3D {
    float x, y, z;

    Point3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
    
    /**
     * @brief Verschiebt einen Punkt entlang eines Vektors.
     * @param vec Der zu addierende Vektor
     * @return Neuer Punkt nach der Addition
     */
    Point3D operator+(const Vector3D& vec) const;
    
    /**
     * @brief Berechnet den Vektor vom übergebenen Punkt zu diesem Punkt.
     * @param p Ein anderer Punkt
     * @return Resultierender Vektor
     */
    Vector3D operator-(const Point3D& p) const;
};

/**
 * @struct Vector3D
 * @brief Repräsentiert einen 3D-Vektor.
 */
struct Vector3D {
    float x, y, z;

    Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : x(x), y(y), z(z) {} 
    
    /**
     * @brief Vektoraddition.
     * @param other Der andere Vektor
     * @return Ergebnis der Addition
     */
    Vector3D operator+(const Vector3D& other) const {
        return {x + other.x, y + other.y, z + other.z};
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
};

/// @see Point3D operator+
inline Point3D Point3D::operator+(const Vector3D& vec) const {
    return {x + vec.x, y + vec.y, z + vec.z};
}

/// @see Point3D operator-
inline Vector3D Point3D::operator-(const Point3D& p) const {
    return {x - p.x, y - p.y, z - p.z};
}

/**
 * @brief Vektoraddition mit Punkt (Kommutativität: Vektor + Punkt = Punkt).
 * @param vec Der Vektor
 * @param p Der Punkt
 * @return Neuer Punkt nach Verschiebung
 */
inline Point3D operator+(const Vector3D& vec, const Point3D& p) {
    return p + vec;
}

/**
 * @struct RGBA
 * @brief Repräsentiert eine Farbe mit Rot, Grün, Blau und Alpha-Kanal.
 */
struct RGBA {
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    double a = 1.0;
};

/**
 * @brief Überladener Stream-Ausgabeoperator für RGBA-Farben.
 * Gibt eine farbkodierte Kurzform zurück.
 * @param os Ausgabestream
 * @param color Farbe im RGBA-Format
 * @return Referenz auf den Ausgabestream
 */
inline std::ostream& operator<<(std::ostream& os, const RGBA& color) {
    float r = color.r, g = color.g, b = color.b;

    if (r == 1.0f && g == 0.0f && b == 0.0f)
        os << "r";  // Red
    else if (r == 0.0f && g == 1.0f && b == 0.0f)
        os << "g";  // Green
    else if (r == 0.0f && g == 0.0f && b == 1.0f)
        os << "b";  // Blue
    else if (r == 1.0f && g == 1.0f && b == 0.0f)
        os << "y";  // Yellow
    else if (r == 1.0f && g == 0.5f && b == 0.0f)
        os << "o";  // Orange
    else if (r == 0.5f && g == 0.0f && b == 0.5f)
        os << "p";  // Purple
    else if (r == 0.0f && g == 1.0f && b == 1.0f)
        os << "c";  // Cyan
    else if (r == 1.0f && g == 1.0f && b == 1.0f)
        os << "w";  // White
    else if (r == 0.0f && g == 0.0f && b == 0.0f)
        os << " ";  // Black
    else
        os << ".";  // Unrecognized / other
    return os;
}

