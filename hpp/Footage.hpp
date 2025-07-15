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
    void classicCottage(const std::string& file, int scale);
    void cottageSpinner(const std::string& file, int scale);
    void cottageSpinnerFrames(const std::string& file, int scale, int frames);
};
