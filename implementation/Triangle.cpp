#include "../hpp/Triangle.hpp"
#include <stdexcept>

Triangle::Triangle(const std::vector<uint32_t>& vertexIndices,
                   const std::array<uint32_t, 3>& normalIndices,
                   u_int16_t materialIndex)
    : vertexIndices(vertexIndices), materialIndex(materialIndex), normalIndices(normalIndices)
{
    if (vertexIndices.size() != 3) {
        throw std::invalid_argument("Triangle requires exactly 3 vertex indices.");
    }
}


const std::vector<uint32_t>& Triangle::getIndices() const {
    return vertexIndices;
}

const std::array<uint32_t, 3>& Triangle::getNormalIndices() const {
    return normalIndices;
}

u_int16_t Triangle::getMaterialIndex() const {
    return materialIndex;
}
