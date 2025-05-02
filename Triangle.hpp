#include "vertex.h"
#include <array>
#include <vector>
#include <cstdint>

class Triangle {
    private: 
        std::vector<uint32_t> vertexIndices;
    public:
        Triangle(const std::vector<uint32_t>& indices);

        const std::vector<uint32_t>& getIndices() const;
};