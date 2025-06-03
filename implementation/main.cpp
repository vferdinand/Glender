#include <iostream>
#include "../hpp/Loader.hpp"
#include "../hpp/Camera.hpp"
#include "../hpp/Image.hpp"
#include "../hpp/Scene.hpp"


#include <chrono>
#include <thread>


int carspinner() {
    /////////////////////////////////////////////////////////////////////
    // Scene Beispiel
    /////////////////////////////////////////////////////////////////////
    // Szene einmalig laden
    std::string file_path_obj = "eyeball.obj";
    std::string file_path_mtl = "cube.mtl";
    Scene scene(file_path_obj);//, file_path_mtl);

    // Kreisbahn-Parameter
    const float radius    = 7.0;    // Abstand von (0,0,0)
    const float height    = 1.4;    // y-Höhe der Kamera
    const float stepAngle = 0.2;   // Drehgeschwindigkeit pro Frame
    float angle = 0.0;
    std::vector<Image> images;
    int numStep = 31;
    // unendliche Render-Schleife
    for (int i = 0; i < numStep; i++) {
        // 1) Berechne neue Kameraposition in der XZ-Ebene
        float camX = radius * std::cos(angle);
        float camZ = radius * std::sin(angle);
        Point3D camPos{ camX, height, camZ };

        // 2) Initialisiere Kamera: Position = camPos, Blickrichtung = auf (0,0,0)
        scene.setCamera(camPos,Vector3D{ -camX, -0.4, -camZ },1.0f, 1.0f, 30, 30);

        // 3) Raytracing & Bild ausgeben
        Image img = scene.generateImage();
        images.push_back(img);

        // 4) Winkel weiterschalten und bei 2π zurücksetzen
        angle += stepAngle;
        if (angle >= 2.0 * M_PI) {
            angle -= 2.0 * M_PI;
        }
        std::cout << "Image " << i << " generated." << std::endl;
    }
    long unsigned int counter = 0;
    while (true)
    {
	std::cout << "\033[2J\033[1;1H";
    	images[counter].print();
        counter++;
        // pause for 200 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        if (counter >= images.size())
            counter = 0;
    }
    
    //image.save("output.png");
}


int main() {

    //carspinner();
    /////////////////////////////////////////////////////////////////////
    // Scene Beispiel
    /////////////////////////////////////////////////////////////////////
    // Szene einmalig laden
    std::string file_path_obj = "house.obj";
    Scene scene(file_path_obj);

    // Kreisbahn-Parameter
    const float radius    = 8.0;    // Abstand von (0,0,0)
    const float height    = 2.8;    // y-Höhe der Kamera
    const float stepAngle = 0.1;   // Drehgeschwindigkeit pro Frame
    float angle = 0.0;

    // unendliche Render-Schleife
    while (angle == 0.0) {
        // 1) Berechne neue Kameraposition in der XZ-Ebene
        float camX = radius * std::cos(angle);
        float camZ = radius * std::sin(angle);
        Point3D camPos{ camX, height, camZ };

        // 2) Initialisiere Kamera: Position = camPos, Blickrichtung = auf (0,0,0)
        scene.setCamera(camPos,Vector3D{ -camX, -0.4, -camZ },1.0f, 1.0f, 58, 58);

        // 3) Raytracing & Bild ausgeben
        Image img = scene.generateImage();
        //img.print();
        img.save("output.ppm");

        // 4) Winkel weiterschalten und bei 2π zurücksetzen
        angle += stepAngle;
        if (angle >= 2.0 * M_PI) {
            angle -= 2.0 * M_PI;
        }
    }
    //image.save("output.png");
}
