#pragma once
#include "structs/Vertex.hpp"
#include <vector>
#include <cstdint>

class Triangle {
    private: 
        std::vector<uint32_t> vertexIndices;
        u_int16_t materialIndex;
        uint32_t normalIndex;

    public:

        /*
        * Ein Dreieck wird durch drei Indizes in der vertexIndices-Liste
        * und einen Farbindex in der colors-Liste dargestellt.
        * Der Farbindex ist optional und wird standardmäßig auf 0 gesetzt.
        */
        Triangle(const std::vector<uint32_t>& vertexIndices, u_int32_t normalIndex, u_int16_t materialIndex = 0);

        const std::vector<uint32_t>& getIndices() const;

        u_int16_t getMaterialIndex() const;
        uint32_t getNormalIndex() const;

};