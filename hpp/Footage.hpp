#pragma once
#include <string>
#include "Image.hpp"
#include "Scene.hpp"

class Footage {
public:
    void classicCar(const std::string& file, int scale);
    void carspinner(const std::string& file, int scale);
    void lightspinner(const std::string& file, int scale);
    void carspinnerFrames(const std::string& file, int scale, int frames);
};
