#include <iostream>
#include "../hpp/Loader.hpp"
#include "../hpp/Camera.hpp"
#include "../hpp/Image.hpp"
#include "../hpp/Scene.hpp"

// Generates real-time images of a car spinning around its center
int carspinner() {
    std::string file_path_obj = "Car.obj";
    Scene scene(file_path_obj);

    const float radius    = 5.3;
    const float height    = 1.4;
    const float stepAngle = 0.04;
    float angle = 0.98f;

    while (true) {
        float camX = radius * std::cos(angle);
        float camZ = radius * std::sin(angle);
        Point3D camPos{ camX, height, camZ };
        scene.setCamera(camPos, Vector3D{ -camX, -0.4, -camZ }, 1.0f, 1.0f, 255, 255);
        Image img = scene.generateImage();
        img.save("Car1.ppm");
        angle += stepAngle;
        if (angle >= 2.0 * M_PI) {
            angle -= 2.0 * M_PI;
        }
    }
}

// Generates real-time images of a car with light direction changing around it
int lightspinner() {
    std::string file_path_obj = "Car.obj";
    Scene scene(file_path_obj);

    Point3D camPos{ 4.0, 2.0, 4.0 };
    Vector3D camDir{ -1.0, -0.4, -1.0};
    scene.setCamera(camPos, camDir, 1.0f, 3);

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
        scene.setLight(lightDir.normalized());
        Image img = scene.generateImage();
        img.save("Car.ppm");
        angle += stepAngle;
        if (angle >= 2.0f * M_PI) angle -= 2.0f * M_PI;
    }
}

// Generates frames of a car with light direction changing around it
void lightspinnerFrames() {
    Scene scene("Car.obj");
    scene.setCamera({4.0f, 2.0f, 4.0f}, {-1.0f, -0.4f, -1.0f}, 1.0f, 8);

    const float PI = 3.14159265f;
    const int steps = 100;
    const float stepAngle = 2 * PI / steps;
    float angle = 0.0f;

    for (int frame = 0; frame < steps; ++frame) {
        float x = std::cos(angle);
        float z = std::sin(angle);
        float y = 1.0f;
        scene.setLight(Vector3D{ x, y, z }.normalized());
        Image img = scene.generateImage();
        img.save("obj/frames/frame_" + std::to_string(frame) + ".ppm");
        angle += stepAngle;
        std::cout << "Frame " << frame << " saved." << std::endl;
    }
}

// Generates frames of a car spinning around its center with a fixed light direction
void carspinnerFrames() {
    Scene scene("Car.obj");

    const float PI = 3.14159265f;
    const float radius = 5.3f;
    const float height = 1.4f;
    const int frames = 100;
    const float stepAngle = 2 * PI / frames;
    float angle = 0.98f;

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

// Generates frames of a car spinning around its center with light direction changing
void combinedSpinnerFrames() {
    Scene scene("Car.obj");

    const float PI = 3.14159265f;
    const int frames = 100;
    const float stepAngle = 2 * PI / frames;
    const float camRadius = 5.3f;
    const float camHeight = 1.4f;
    float angle = 0.0f;

    for (int frame = 0; frame < frames; ++frame) {
        float camX = camRadius * std::cos(angle);
        float camZ = camRadius * std::sin(angle);
        Point3D camPos{ camX, camHeight, camZ };
        Vector3D camDir{ -camX, -0.4f, -camZ };
        scene.setCamera(camPos, camDir, 1.0f, 8);

        float lx = std::cos(angle);
        float lz = std::sin(angle);
        float ly = 1.0f;
        scene.setLight(Vector3D{ lx, ly, lz }.normalized());

        Image img = scene.generateImage();
        std::string fname = "obj/frames3/frame_" + std::to_string(frame) + ".ppm";
        img.save(fname);

        std::cout << "Saved " << fname << "\n";
        angle += stepAngle;
    }
}

// Generates one image of a car with a fixed camera position and light direction
void classic() {
    Scene scene("Car.obj");

    Point3D camPos{ 4.0, 2.0, 4.0 };
    Vector3D camDir{ -1.0, -0.4, -1.0};

    scene.setLight(Vector3D{ 1.0, 1.0, 1.0 }.normalized());
    
    scene.setCamera(camPos, camDir, 1.0f, 24);

    Image img = scene.generateImage();

    img.save("Car.ppm");
}

void classicMutter() {
    Scene scene("mutter_gewinde_200.obj");

    Point3D camPos{ 18.0, 2.0, 18.0 };
    Vector3D camDir{ -1.0, -0.1, -1.0};

    scene.setLight(Vector3D{ 1.0, 1.0, 1.0 }.normalized());
    
    scene.setCamera(camPos, camDir, 1.0f, 12);

    Image img = scene.generateImage();

    img.save("Car.ppm");
}

void mutterSpinnerFrames(){
    Scene scene("mutter_gewinde_200.obj");

    const float PI = 3.14159265f;
    const float radius = 24.3f;
    const float height = 2.0f;
    const int frames = 360;
    const float stepAngle = 2 * PI / frames;
    float angle = 0.98f;

    for (int frame = 0; frame < frames; ++frame) {
        float camX = radius * std::cos(angle);
        float camZ = radius * std::sin(angle);
        scene.setCamera(
            Point3D{ camX, height, camZ },
            Vector3D{ -camX, -1.7f, -camZ },
            1.0f, 8
        );

        float lx = std::cos(angle);
        float lz = std::sin(angle);
        float ly = 1.0f;
        scene.setLight(Vector3D{ lx, ly, lz }.normalized());

        Image img = scene.generateImage();
        char fname[64];
        std::snprintf(fname, sizeof(fname), "obj/framesMutter/frame_%03d.ppm", frame);
        img.save(fname);
        std::cout << "Saved " << fname << "\n";
        angle += stepAngle;
    }
}

int main() {
    //carspinner();
    //lightspinner();
    //lightspinnerFrames();
    //carspinnerFrames();
    //combinedSpinnerFrames();
    classicMutter();
    //mutterSpinnerFrames();
    return 0;
}