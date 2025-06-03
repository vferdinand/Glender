#include "../hpp/Triangle.hpp"
#include <stdexcept>

/*
 * Ein Dreieck wird durch drei Indizes in der vertexIndices-Liste
 * und einen Farbindex in der colors-Liste dargestellt.
 * Der Farbindex ist optional und wird standardmäßig auf 0 gesetzt.
 */
Triangle::Triangle(const std::vector<uint32_t>& vertexIndices, u_int16_t materialIndex) {
    if (vertexIndices.size() != 3) {
        throw std::invalid_argument("Triangle requires exactly 3 vertex indices.");
    }
    this->vertexIndices = vertexIndices;
    this->materiaIndex = materiaIndex;
}

const std::vector<uint32_t>& Triangle::getIndices() const {
    return vertexIndices;
}

u_int16_t Triangle::getMaterialIndex() const{
    return materiaIndex;
}