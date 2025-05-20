#include <iostream>
#include "../hpp/Loader.hpp"
#include "../hpp/Camera.hpp"
#include "../hpp/Image.hpp"
#include "../hpp/Scene.hpp"
//#include "Vertex.hpp"
//#include "Triangle.hpp"

int main() {
    std::string file_path_obj = "house.obj";
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
    camera.initialize(Point3D{0, 0, 0}, Vector3D {1, -2, 1}, 2.0f, 2.0f, 5, 5);
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
    Scene scene(file_path_obj, file_path_mtl);

    // Kreisbahn-Parameter
    const double radius    = 8.0;    // Abstand von (0,0,0)
    const double height    = 8.0;    // y-Höhe der Kamera
    const double stepAngle = 0.04;   // Drehgeschwindigkeit pro Frame

    double angle = 0.0;

    // unendliche Render-Schleife
    while (true) {
        // 1) Berechne neue Kameraposition in der XZ-Ebene
        double camX = radius * std::cos(angle);
        double camZ = radius * std::sin(angle);
        Point3D camPos{ camX, height, camZ };

        // 2) Initialisiere Kamera: Position = camPos, Blickrichtung = auf (0,0,0)
        scene.camera.initialize(
            camPos,
            Vector3D{ -camX, -6, -camZ }, //Vector3D{ -camX, -height, -camZ },  // Richtung: Ziel (0,0,0) minus Position
            0.7f, 0.7f,
            30, 40
        );

        // 3) Raytracing & Bild ausgeben
        Image img = scene.generateImage();
        img.print();

        // 4) Winkel weiterschalten und bei 2π zurücksetzen
        angle += stepAngle;
        if (angle >= 2.0 * M_PI) {
            angle -= 2.0 * M_PI;
        }
    }

    return 0;

    
    //image.save("output.png");
}
