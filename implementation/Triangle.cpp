#include "../hpp/Triangle.hpp"
#include <stdexcept>

Triangle::Triangle(const std::vector<uint32_t>& vertexIndices, u_int16_t colorIndex) {
    if (vertexIndices.size() != 3) {
        throw std::invalid_argument("Triangle requires exactly 3 vertex indices.");
    }
    this->vertexIndices = vertexIndices;
    this->colorIndex = colorIndex;
}

const std::vector<uint32_t>& Triangle::getIndices() const {
    return vertexIndices;
}

const u_int16_t Triangle::getColorIndex(){
    return colorIndex;
}