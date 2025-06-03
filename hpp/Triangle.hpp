#pragma once
#include "Structs.hpp"
#include <array>
#include <vector>
#include <cstdint>

class Triangle {
    private: 
        std::vector<uint32_t> vertexIndices;
        u_int16_t colorIndex;
        Vector3D normal;

    public:
        Triangle(const std::vector<uint32_t>& vertexIndices, u_int16_t colorIndex = 0);

        const std::vector<uint32_t>& getIndices() const;
        u_int16_t getColorIndex() const;
        const Vector3D& getNormal() const;

};