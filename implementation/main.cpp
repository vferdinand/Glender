#include <iostream>
#include "../hpp/Loader.hpp"
#include "../hpp/Camera.hpp"
#include "../hpp/Image.hpp"
#include "../hpp/Scene.hpp"


//#include <chrono>
//#include <thread>


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
    const float stepAngle = 0.04;   // Drehgeschwindigkeit pro Frame
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
        img.save("Car1.ppm");

        // 4) Winkel weiterschalten und bei 2π zurücksetzen
        angle += stepAngle;
        if (angle >= 2.0 * M_PI) {
            angle -= 2.0 * M_PI;
        }
    }
}
int lightspinner() {
    std::string file_path_obj = "Car.obj";
    Scene scene(file_path_obj);

    // Kamera bleibt fix
    Point3D camPos{ 4.0, 2.0, 4.0 };
    Vector3D camDir{ -1.0, -0.4, -1.0};
    scene.setCamera(camPos, camDir, 1.0f, 3);

    // Lichtvektor dreht sich in der XZ-Ebene, y bleibt konstant
    const float PI = 3.14159265f;
	const int steps = 40;
	const float radius = 1.0f;
	const float stepAngle = 2 * PI / steps;
    float y = 1.0f; 
	float angle = 0.0f;


    while (true) {
        float x = radius * std::cos(angle);
		float z = radius * std::sin(angle);

        Vector3D lightDir{ x, y, z };
        scene.light.setGlobalLightVec(lightDir.normalized());

        Image img = scene.generateImage();
        img.save("Car.ppm");

        angle += stepAngle;
        if (angle >= 2.0f * M_PI) angle -= 2.0f * M_PI;
    }
}


void lightspinnerFrames()
{
    Scene scene("Car.obj");
    // fix camera:
    scene.setCamera({4.0f, 2.0f, 4.0f}, {-1.0f, -0.4f, -1.0f}, 1.0f, 8);

    const float PI        = 3.14159265f;
    const int   steps     = 100;
    const float stepAngle = 2 * PI / steps;
    float       angle     = 0.0f;

    for (int frame = 0; frame < steps; ++frame) {
        // spin light at 45° elevation:
        float x = std::cos(angle);
        float z = std::sin(angle);
        float y = 1.0f; 
        scene.light.setGlobalLightVec(Vector3D{ x, y, z }.normalized());

        // render & save
        Image img = scene.generateImage();
        img.save("obj/frames/frame_" + std::to_string(frame) + ".ppm");

        angle += stepAngle;
        std::cout << "Frame " << frame << " saved." << std::endl;
    }
}
void carspinnerFrames()
{
    Scene scene("Car.obj");

    const float PI        = 3.14159265f;
    const float radius    = 5.3f;
    const float height    = 1.4f;
    const int   frames    = 100;
    const float stepAngle = 2 * PI / frames;
    float       angle     = 0.98f;

    for (int frame = 0; frame < frames; ++frame) {
        float camX = radius * std::cos(angle);
        float camZ = radius * std::sin(angle);
        scene.setCamera(
            Point3D{ camX, height, camZ },
            Vector3D{ -camX, -0.4f, -camZ },
            1.0f, 8
        );

        Image img = scene.generateImage();
        img.save("obj/frames2/frame_" + std::to_string(frame) + ".ppm");

        angle += stepAngle;
    }
}

void combinedSpinnerFrames()
{
    Scene scene("Car.obj");

    const float PI        = 3.14159265f;
    const int   frames    = 100;
    const float stepAngle = 2 * PI / frames;
    const float camRadius = 5.3f;
    const float camHeight = 1.4f;
    float       angle     = 0.0f;

    // Make sure the output directory exists:
    // mkdir -p obj/frames3
    for (int frame = 0; frame < frames; ++frame) {
        // --- camera spin ---
        float camX = camRadius * std::cos(angle);
        float camZ = camRadius * std::sin(angle);
        Point3D camPos{ camX, camHeight, camZ };
        Vector3D camDir{ -camX, -0.4f, -camZ };  // look toward origin
        scene.setCamera(camPos, camDir, 1.0f, 8);

        // --- light spin (same angle, so light appears fixed relative to camera) ---
        float lx = std::cos(angle);
        float lz = std::sin(angle);
        float ly = 1.0f;                        // 45° elevation
        scene.light.setGlobalLightVec(Vector3D{ lx, ly, lz }.normalized());

        // --- render & save ---
        Image img = scene.generateImage();
        std::string fname = "obj/frames3/frame_" + std::to_string(frame) + ".ppm";
        img.save(fname);

        std::cout << "Saved " << fname << "\n";
        angle += stepAngle;
    }
}

int main() {
    //carspinner();
    lightspinner();
    //lightspinnerFrames();
    //carspinnerFrames();
    //combinedSpinnerFrames();
    return 0;
    Scene scene("Car.obj");

    Point3D camPos{ 4.0, 2.0, 4.0 };
    Vector3D camDir{ -1.0, -0.4, -1.0};

    scene.light.setGlobalLightVec(Vector3D{ 1.0, 1.0, 1.0 }.normalized());

    //scene.setCamera(camPos ,camDir ,1.0f, 0.5f, 500, 250);//7680, 4320);
    /**
     * @brief Kurzübersicht zur Referenz der Werte & ihr scaling im 16:9 Format
     * 1   - 160x90
     * 8   - 1280x720   (HD)
     * 12  - 1920x1080  (Full HD)
     * 16  - 2560x1440  (QHD)
     * 24  - 3840x2160 (4K)
     */
    scene.setCamera(camPos, camDir, 1.0f, 24);

    Image img = scene.generateImage();

    img.save("Car.ppm");
}
