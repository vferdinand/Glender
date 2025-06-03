#pragma once
#include "Structs.hpp"
#include <array>
#include <vector>
#include <cstdint>

class Triangle {
    private: 
        std::vector<uint32_t> vertexIndices;
        u_int16_t materiaIndex;

    public:
        Triangle(const std::vector<uint32_t>& vertexIndices, u_int16_t materialIndex = 0);

        const std::vector<uint32_t>& getIndices() const;
        u_int16_t getMaterialIndex() const;
};