#pragma once
#include <string>
#include "Image.hpp"
#include "Scene.hpp"

class Footage {
public:
    void mutterSpinnerFrames(int scale);
    void classicMutter(int scale);
    void classicMirrorTest(int scale);
    void classicLiving(int scale);
    void classicRussian(int scale);
    void classicGlassCube(int scale);
    void classicCar(int scale);
    void combinedSpinnerFrames(int scale);
    void carspinnerFrames(int scale);
    void lightspinnerFrames(int scale);
    int lightspinner(int scale);
    int carspinner(int scale);
};