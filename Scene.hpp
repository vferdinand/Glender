#include <vector>
#include "Triangle.hpp"

class Scene {
    private:
        std::vector<Triangle> triangles;
    public:
        void addTriangle(Triangle tri);

        const std::vector<Triangle>& getTriangles() const;
};
