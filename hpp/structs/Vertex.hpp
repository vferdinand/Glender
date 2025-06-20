#pragma once

#include <stdexcept>

struct Vertex;
/**
 * @struct Vertex
 * @brief Repräsentiert einen 3D-Vertex ohne spezielle Semantik.
 */
struct Vertex {
    float x, y, z;

    float operator[](int i) const {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw std::out_of_range("Vertex index out of range");
        }
    }

    float& operator[](int i) {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw std::out_of_range("Vertex index out of range");
        }
    }
};