#include <iostream>
#include "../hpp/Loader.hpp"
#include "../hpp/Camera.hpp"
#include "../hpp/Image.hpp"
#include "../hpp/Scene.hpp"
//#include "Vertex.hpp"
//#include "Triangle.hpp"

int main() {
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
    // Szene einmalig laden
    std::string file_path_obj = "house.obj";
    std::string file_path_mtl = "cube.mtl";
    Scene scene(file_path_obj, file_path_mtl);

    // Kreisbahn-Parameter
    const float radius    = 7.0;    // Abstand von (0,0,0)
    const float height    = 5.6;    // y-Höhe der Kamera
    const float stepAngle = 0.05;   // Drehgeschwindigkeit pro Frame

    float angle = 0.0;

    // unendliche Render-Schleife
    while (true) {
        // 1) Berechne neue Kameraposition in der XZ-Ebene
        float camX = radius * std::cos(angle);
        float camZ = radius * std::sin(angle);
        Point3D camPos{ camX, height, camZ };

        // 2) Initialisiere Kamera: Position = camPos, Blickrichtung = auf (0,0,0)
        scene.setCamera(camPos,Vector3D{ -camX, -3, -camZ },1.0f, 1.0f, 100, 100);

        // 3) Raytracing & Bild ausgeben
        Image img = scene.generateImage();
        img.print();

        // 4) Winkel weiterschalten und bei 2π zurücksetzen
        angle += stepAngle;
        if (angle >= 2.0 * M_PI) {
            angle -= 2.0 * M_PI;
        }
    }
    //image.save("output.png");
}
