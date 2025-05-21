#include <iostream>
#include "../hpp/Loader.hpp"
#include "../hpp/Camera.hpp"
#include "../hpp/Image.hpp"
#include "../hpp/Scene.hpp"
//#include "Vertex.hpp"
//#include "Triangle.hpp"

int main() {
    std::string file_path_obj = "cube2.obj";
    std::string file_path_mtl = "cube.mtl";

    /*
    /////////////////////////////////////////////////////////////////////
    // Loader Beispiel 
    /////////////////////////////////////////////////////////////////////
    Loader loader;

    loader.loadOBJ(file_path_obj, file_path_mtl);

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
        std::cout << "f " << idx[0] << " " << idx[1] << " " << idx[2] << " color: " << t.getColorIndex() << "\n";
    }

    std::cout << "\nLoaded " << colors.size() << " colors:\n";
    for (const auto& c : colors) {
        std::cout << "r " << c.r << " g " << c.g << " b " << c.b << " a " << c.a << "\n";
    }
    */
   
    /*
    /////////////////////////////////////////////////////////////////////
    // Camera Beispiel
    /////////////////////////////////////////////////////////////////////

    Camera camera;
    std::vector<Ray> rays = camera.generate_rays();

    for (size_t i = 1; i < rays.size() + 1; ++i) {
        const auto& ray = rays[i];
        std::cout << "Ray " << i << ": Directio = ("
                  << ray.getDirection().x << ", "
                  << ray.getDirection().y << ", "
                  << ray.getDirection().z << ")\n";
    }
    */

    /////////////////////////////////////////////////////////////////////
    // Scene Beispiel
    /////////////////////////////////////////////////////////////////////
    Scene scene(file_path_obj, file_path_mtl);
    Image image = scene.generateImage();
    image.print();
    //image.save("output.png");
}
