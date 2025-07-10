#include "../hpp/Footage.hpp"

void Footage::classicCar(const std::string& file, int scale) {
    Scene scene(file);
    Point3D camPos{4.0, 2.0, 4.0};
    Vector3D camDir{-1.0, -0.4, -1.0};
    scene.setLight(Vector3D{1.0, 1.0, 1.0}.normalized());
    scene.setCamera(camPos, camDir, 1.0f, scale);
    Image img = scene.generateImage();
    img.save("output_classicCar.ppm");
}

void Footage::carspinner(const std::string& file, int scale) {
    Scene scene(file);
    const float radius = 5.3f;
    const float height = 1.4f;
    const float stepAngle = 0.04f;
    float angle = 0.98f;

    while (true) {
        float camX = radius * std::cos(angle);
        float camZ = radius * std::sin(angle);
        Point3D camPos{camX, height, camZ};
        scene.setCamera(camPos, Vector3D{-camX, -0.4f, -camZ}, 1.0f, scale);
        scene.setLight(Vector3D{1.0f, 1.0f, 1.0f}.normalized());
        Image img = scene.generateImage();
        img.save("output_carspinner.ppm");
        angle += stepAngle;
        if (angle >= 2.0f * M_PI) angle -= 2.0f * M_PI;
    }
}

void Footage::lightspinner(const std::string& file, int scale) {
    Scene scene(file);
    Point3D camPos{4.0, 2.0, 4.0};
    Vector3D camDir{-1.0, -0.4, -1.0};
    scene.setCamera(camPos, camDir, 1.0f, scale);

    const float PI = 3.14159265f;
    const int steps = 40;
    const float radius = 1.0f;
    const float stepAngle = 2 * PI / steps;
    float y = 1.0f;
    float angle = 0.0f;

    while (true) {
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);
        Vector3D lightDir{x, y, z};
        scene.setLight(lightDir.normalized());
        Image img = scene.generateImage();
        img.save("output_lightspinner.ppm");
        angle += stepAngle;
        if (angle >= 2.0f * M_PI) angle -= 2.0f * M_PI;
    }
}

void Footage::carspinnerFrames(const std::string& file, int scale, int frames) {
    Scene scene(file);
    const float PI = 3.14159265f;
    const float radius = 5.3f;
    const float height = 1.4f;
    const float stepAngle = 2 * PI / frames;
    float angle = 0.98f;

    for (int frame = 0; frame < frames; ++frame) {
        float camX = radius * std::cos(angle);
        float camZ = radius * std::sin(angle);
        scene.setCamera(Point3D{camX, height, camZ}, Vector3D{-camX, -0.4f, -camZ}, 1.0f, scale);
        scene.setLight(Vector3D{1.0, 1.0, 1.0}.normalized());
        Image img = scene.generateImage();
        std::string fname = "frames/frame_" + std::to_string(frame) + ".ppm";
        img.save(fname);
        std::cout << "Saved " << fname << "\n";
        angle += stepAngle;
    }
}