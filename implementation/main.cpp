#include <iostream>
#include "../hpp/Loader.hpp"
#include "../hpp/Camera.hpp"
#include "../hpp/Image.hpp"
#include "../hpp/Scene.hpp"


#include <chrono>
#include <thread>


int carspinner() {
    //carspinner();
    /////////////////////////////////////////////////////////////////////
    // Scene Beispiel
    /////////////////////////////////////////////////////////////////////
    // Szene einmalig laden
    std::string file_path_obj = "Car.obj";
    Scene scene(file_path_obj);

    // Kreisbahn-Parameter
    const float radius    = 5.3;    // Abstand von (0,0,0)
    const float height    = 1.4;    // y-Höhe der Kamera
    const float stepAngle = 0.1;   // Drehgeschwindigkeit pro Frame
    float angle = 0.98f;//5.4f;

    // unendliche Render-Schleife
    while (true) {
        // 1) Berechne neue Kameraposition in der XZ-Ebene
        float camX = radius * std::cos(angle);
        float camZ = radius * std::sin(angle);
        Point3D camPos{ camX, height, camZ };

        // 2) Initialisiere Kamera: Position = camPos, Blickrichtung = auf (0,0,0)
        scene.setCamera(camPos,Vector3D{ -camX, -0.4, -camZ },1.0f, 1.0f, 255, 255);

        // 3) Raytracing & Bild ausgeben
        Image img = scene.generateImage();
        //img.print();
        img.save("Car.ppm");

        // 4) Winkel weiterschalten und bei 2π zurücksetzen
        angle += stepAngle;
        if (angle >= 2.0 * M_PI) {
            angle -= 2.0 * M_PI;
        }
    }
}


int main() {
    //carspinner();
    Scene scene("Car.obj");

    Point3D camPos{ 9.0, 5.0, 9.0 };
    Vector3D camDir{ -1.0, -0.4, -1.0};
    /**
     * @brief Kurzübersicht zur Referenz der Werte & ihr scaling im 16:9 Format
     * 0.7f - groß                  | * 1   - 160x90
     * 1.4f - medium                | * 8   - 1280x720   (HD)
     * 2.1f - klein                 | * 12  - 1920x1080  (Full HD)
     * 4.0f - fast schon zu klein   | * 16  - 2560x1440  (QHD)
     * 8.0f - klein af              | * 240 - 3840x2160 (4K)
     */
    scene.setCamera(camPos, camDir, 0.7f, 12);

    Image img = scene.generateImage();

    img.save("Car.ppm");
}
