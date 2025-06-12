#include "../hpp/Triangle.hpp"

Triangle::Triangle(const std::vector<uint32_t>& vertexIndices, uint32_t normalIndex, u_int16_t materialIndex) {
    if (vertexIndices.size() != 3) {
        throw std::invalid_argument("Triangle requires exactly 3 vertex indices.");
    }
    this->vertexIndices = vertexIndices;

    this->materialIndex = materialIndex;

    this->normalIndex = normalIndex;
}

const std::vector<uint32_t>& Triangle::getIndices() const {
    return vertexIndices;
}

u_int16_t Triangle::getMaterialIndex() const{
    return materialIndex;
}

uint32_t Triangle::getNormalIndex() const {
    return normalIndex;
}