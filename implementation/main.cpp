#include "../hpp/Footage.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

// --- Auflösungsskala aus String ---
int getScaleFromResolution(const std::string& res) {
    if (res == "mini") return 2; // klein
    if (res == "test") return 4; // klein
    if (res == "fullhd") return 12; // 1920x1080
    if (res == "2k") return 16;      // 2048x1080
    if (res == "4k") return 24;     // 3840x2160
    if(res == "8k") return 48;      // 7680x4320
    if(res == "16k") return 96;      // 7680x4320
    std::cerr << "Unbekannte Auflösung '" << res << "', verwende Full HD (12).\n";
    return 12;
}

int main(int argc, char* argv[]) {

    Footage footage;

    if (argc < 2) {
        std::cout << "Usage: ./main <obj-file> [resolution] [mode] [frames (nur für carspinnerframes)]\n";
        std::cout << "Resolution options: hd, fullhd, 4k (default: fullhd)\n";
        std::cout << "Modes: classic, carspinner, lightspinner, carspinnerframes\n";
        return 1;
    }

    std::string file = argv[1];

    std::string res = "fullhd";
    std::string mode = "classic";
    int frames = 0; 

    if (argc >= 3) res = argv[2];
    if (argc >= 4) mode = argv[3];
    if (argc >= 5) frames = std::atoi(argv[4]);

    int scale = getScaleFromResolution(res);

    std::cout << "Datei: " << file << "\nAuflösung: " << res << " (Skalierung: " << scale << ")\nModus: " << mode << "\n";

    if (mode == "classic") {
        footage.classicCar(file, scale);
    } else if (mode == "carspinner") {
        footage.carspinner(file, scale);
    } else if (mode == "lightspinner") {
        footage.lightspinner(file, scale);
    } else if (mode == "carspinnerframes") {
        if (frames <= 0) {
            std::cerr << "Für Modus 'carspinnerframes' muss eine positive Anzahl an Frames angegeben werden.\n";
            return 1;
        }
        footage.carspinnerFrames(file, scale, frames);
    }else if (mode == "cottage") {
        footage.classicCottage(file, scale);
    } else if (mode == "cottagespinner") {
        footage.cottageSpinner(file, scale);
    }else if (mode == "cottagespinnerframes") {
        if (frames <= 0) {
            // ./main cottage_obj.obj test cottagespinnerframes 20
            std::cerr << "Für Modus 'cottagespinnerframes' muss eine positive Anzahl an Frames angegeben werden.\n";
            return 1;
        }
        footage.cottageSpinnerFrames(file, scale, frames);
    } else {
        std::cerr << "Unbekannter Modus '" << mode << "'. Verfügbare Modi: classic, carspinner, lightspinner, carspinnerframes\n";
        return 1;
    }

    return 0;
}
