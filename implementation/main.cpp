#include "../hpp/Footage.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

std::string getBaseName(const std::string& path) {
    auto pos = path.find_last_of("/\\");
    std::string name = (pos == std::string::npos ? path : path.substr(pos + 1));
    auto dot = name.find_last_of('.');
    return (dot == std::string::npos ? name : name.substr(0, dot));
}

int getScaleFromResolution(const std::string& res) {
    if (res == "hd")      return 8;   // 1280×720
    if (res == "fullhd")  return 12;  // 1920×1080
    if (res == "4k")      return 24;  // 3840×2160
    if (res == "8k")      return 48;  // 7680×4320
    if (res == "16k")     return 96;  // 15360×8640
    std::cerr << "Unbekannte Auflösung '" << res 
              << "', verwende Full HD (12).\n";
    return 12;// 2) Auflösung einlesen oder Default „fullhd“
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./main <obj-file> [resolution]\n";
        std::cerr << "Resolution options: hd, fullhd, 4k, 8k, 16k (default: fullhd)\n";
        return 1;
    }

    std::string file = argv[1];
    std::string base = getBaseName(file);

    std::string res = (argc >= 3 ? argv[2] : "fullhd");
    int scale = getScaleFromResolution(res);

    std::cout << "Datei: " << file 
              << "\nAuflösung: " << res << " (Scale=" << scale << ")"
              << "\nErkannter Basisname: " << base << "\n\n";

    Footage footage;

    if (base == "Russian_Gamingsetup") {
        footage.classicRussian(scale);
    }
    else if (base == "GlassCube") {
        footage.classicGlassCube(scale);
    }
    else if (base == "Living_Room" || base == "LivingRoom") {
        footage.classicLiving(scale);
    }
    else if (base == "mirror_test") {
        footage.classicMirrorTest(scale);
    }
    else if (base == "mutter_gewinde_60") {
        footage.classicMutter(scale);
    }
    else if (base == "mutter_gewinde_200") {
        footage.mutterSpinnerFrames(scale);
    }
    else if (base == "combinedSpinnerFrames") {
        footage.combinedSpinnerFrames(scale);
    }
    else if (base == "Car" || base == "car") {
        footage.classicCar(scale);
    }
    else {
        
        if (base.find("spinner") != std::string::npos) {
            footage.carspinnerFrames(scale);
        }
        else {
            footage.classicCar(scale);
        }
    }

    return 0;
}
