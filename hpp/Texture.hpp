#pragma once
#include <vector>
#include <string>
#include "Hitpoint.hpp"
#include "structs/RGBA.hpp"

class Texture {
private:
    std::string filePath;         ///< Pfad zur Texturdatei
    std::vector<RGBA> pixels;  ///< Pixel-Daten der Textur
    uint32_t width;            ///< Breite der Textur
    uint32_t height;           ///< Höhe der Textur
public:
    Texture(const std::string& filePath);
    RGBA sample(const Vector3D& uv) const;
    uint32_t getWidth() const;
    uint32_t getHeight() const;
};