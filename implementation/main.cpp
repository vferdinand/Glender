#include <iostream>
#include "../hpp/Loader.hpp"
#include "../hpp/Camera.hpp"
//#include "Vertex.hpp"
//#include "Triangle.hpp"

int main() {
   /* std::string file_path_obj = "test.obj";

    Loader loader;

    loader.loadOBJ(file_path_obj);

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

    return 0; */

    Camera camera;
    //camera.initialize(Point3D{0, 0, 0}, Vector3D {1, -2, 1}, 2.0f, 2.0f, 5, 5);
    std::vector<Ray> rays = camera.generate_rays();

    for (size_t i = 1; i < rays.size() + 1; ++i) {
        const auto& ray = rays[i];
        std::cout << "Ray " << i << ": Directio = ("
                  << ray.getDirection().x << ", "
                  << ray.getDirection().y << ", "
                  << ray.getDirection().z << ")\n";
    }
}
