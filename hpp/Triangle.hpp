#pragma once
#include "structs/Vertex.hpp"
#include <vector>
#include <cstdint>
#include <array>

class Triangle {
private:
    std::vector<uint32_t> vertexIndices;
    std::vector<uint32_t> textureIndices;
    u_int16_t materialIndex;
    std::array<uint32_t, 3> normalIndices;

public:
    Triangle(const std::vector<uint32_t>& vertexIndices, const std::array<uint32_t, 3>& normalIndices, u_int16_t materialIndex = 0,  const std::vector<uint32_t>& textureIndices = {0,0});
    const std::vector<uint32_t>& getIndices() const;
    const std::vector<uint32_t>& getTextureIndices() const;
    const std::array<uint32_t, 3>& getNormalIndices() const;
    u_int16_t getMaterialIndex() const;
};

