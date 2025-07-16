#pragma once

#include <iostream>

/**
 * @struct RGBA
 * @brief Repräsentiert eine Farbe mit Rot, Grün, Blau und Alpha-Kanal.
 */
struct RGBA {
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    double a = 1.0;

    RGBA operator*(float value) const {
        return {r * value, g * value, b * value, a};
    }

    RGBA operator+(RGBA col) const {
        return {r + col.r, g + col.g, b + col.b,a + col.a};
    }

    RGBA operator*(const RGBA& other) const {
    return {r * other.r, g * other.g, b * other.b, a * other.a};
    
    }

    RGBA clamp(){
        if (r > 1.0) r = 1.0;
        if (g > 1.0) g = 1.0;
        if (b > 1.0) b = 1.0;
        if (a > 1.0) a = 1.0;
        if (r < 0.0) r = 0.0;
        if (g < 0.0) g = 0.0;
        if (b < 0.0) b = 0.0;
        if (a < 0.0) a = 0.0;
        return {r, g, b, a};
    }
};

/**
 * @brief Überladener Stream-Ausgabeoperator für RGBA-Farben.
 * Gibt eine farbkodierte Kurzform zurück.
 * @param os Ausgabestream
 * @param color Farbe im RGBA-Format
 * @return Referenz auf den Ausgabestream
 */
inline std::ostream& operator<<(std::ostream& os, const RGBA& color) {
    os << "("
       << color.r << ", "
       << color.g << ", "
       << color.b << ", "
       << color.a << ")";
    return os;
}
