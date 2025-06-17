#include "../hpp/Spinner.hpp"
#include <cmath>
#include <iostream>

void Spinner::carSpinner() {
    Scene scene("Car.obj");

    const float radius    = 5.3f;
    const float height    = 1.4f;
    const float stepAngle = 0.04f;
    float angle = 0.98f;

    while (true) {
        float camX = radius * std::cos(angle);
        float camZ = radius * std::sin(angle);
        Point3D camPos{ camX, height, camZ };
        scene.setCamera(camPos, Vector3D{ -camX, -0.4f, -camZ }, 1.0f, 1.0f, 255, 255);

        Image img = scene.generateImage();
        img.save("Car1.ppm");

        angle += stepAngle;
        if (angle >= 2.0f * M_PI) {
            angle -= 2.0f * M_PI;
        }
    }
}

void Spinner::lightSpinner() {
    Scene scene("Car.obj");

    Point3D camPos{ 4.0f, 2.0f, 4.0f };
    Vector3D camDir{ -1.0f, -0.4f, -1.0f };
    scene.setCamera(camPos, camDir, 1.0f, 3);

    const float PI = 3.14159265f;
    const int steps = 40;
    const float radius = 1.0f;
    const float stepAngle = 2 * PI / steps;
    float angle = 0.0f;
    float y = 1.0f;

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

void Spinner::lightSpinnerFrames() {
    Scene scene("Car.obj");
    scene.setCamera({ 4.0f, 2.0f, 4.0f }, { -1.0f, -0.4f, -1.0f }, 1.0f, 8);

    const float PI = 3.14159265f;
    const int steps = 100;
    const float stepAngle = 2 * PI / steps;
    float angle = 0.0f;

    for (int frame = 0; frame < steps; ++frame) {
        float x = std::cos(angle);
        float z = std::sin(angle);
        float y = 1.0f;
        scene.light.setGlobalLightVec(Vector3D{ x, y, z }.normalized());

        Image img = scene.generateImage();
        img.save("obj/frames/frame_" + std::to_string(frame) + ".ppm");

        angle += stepAngle;
        std::cout << "Frame " << frame << " saved." << std::endl;
    }
}

void Spinner::carSpinnerFrames() {
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
        scene.setCamera({ camX, height, camZ }, { -camX, -0.4f, -camZ }, 1.0f, 8);

        Image img = scene.generateImage();
        img.save("obj/frames2/frame_" + std::to_string(frame) + ".ppm");

        angle += stepAngle;
    }
}

void Spinner::combinedSpinnerFrames() {
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
        scene.light.setGlobalLightVec(Vector3D{ lx, ly, lz }.normalized());

        Image img = scene.generateImage();
        std::string fname = "obj/frames3/frame_" + std::to_string(frame) + ".ppm";
        img.save(fname);

        std::cout << "Saved " << fname << "\n";
        angle += stepAngle;
    }
}
