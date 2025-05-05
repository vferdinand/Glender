#include <iostream>
#include "../hpp/Loader.hpp"
//#include "Vertex.hpp"
//#include "Triangle.hpp"

int main() {
    std::string file_path_obj = "test.obj";

    Loader loader(file_path_obj);

    loader.load();

    const std::vector<Vertex>& vertices = loader.getVertices();
    const std::vector<Triangle>& triangles = loader.getTriangles();

    std::cout << "Loaded " << vertices.size() << " vertices:\n";
    for (const auto& v : vertices) {
        std::cout << "v " << v.x << " " << v.y << " " << v.z << "\n";
    }

    std::cout << "\nLoaded " << triangles.size() << " triangles:\n";
    for (const auto& t : triangles) {
        const auto& idx = t.getIndices();
        std::cout << "f " << idx[0] << " " << idx[1] << " " << idx[2] << "\n";
    }

    return 0;
}