#pragma once
#include <string>
#include "../hpp/Image.hpp"
#include "../hpp/Scene.hpp"

class Footage {
public:
    void classicCar(const std::string& file, int scale);
    void carspinner(const std::string& file, int scale);
    void lightspinner(const std::string& file, int scale);
    void carspinnerFrames(const std::string& file, int scale, int frames = 100);
};

