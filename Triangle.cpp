#include "Triangle.h"
#include <stdexcept>

Triangle::Triangle(const std::vector<uint32_t>& indices) {
    if (indices.size() != 3) {
        throw std::invalid_argument("Triangle requires exactly 3 vertex indices.");
    }
}

const std::vector<uint32_t>& Triangle::getIndices() const {
    return vertexIndices;
}