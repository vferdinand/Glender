#include <iostream>
#include "../hpp/Loader.hpp"
//#include "Vertex.hpp"
//#include "Triangle.hpp"

int main() {
    std::string file_path_obj = "test.obj";

    Loader loader;

    loader.loadOBJ(file_path_obj);

    const std::vector<Vertex>& vertices = loader.getVertices();
    const std::vector<Triangle>& triangles = loader.getTriangles();
    const std::vector<RGBA>& colors = loader.getColors();

    std::cout << "Loaded " << vertices.size() << " vertices:\n";
    for (const auto& v : vertices) {
        std::cout << "v " << v.x << " " << v.y << " " << v.z << "\n";
    }

    std::cout << "\nLoaded " << triangles.size() << " triangles:\n";
    for (const auto& t : triangles) {
        const auto& idx = t.getIndices();
        std::cout << "f " << idx[0] << " " << idx[1] << " " << idx[2] << "\n";
    }

    std::cout << "\nLoaded " << colors.size() << " colors:\n";
    for (const auto& c : colors) {
        std::cout << "r " << c.r << " g " << c.g << " b " << c.b << " a " << c.a << "\n";
    }

    return 0;
}
