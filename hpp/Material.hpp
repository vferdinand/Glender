#pragma once

#include "Structs.hpp"

class Material {
    private:
        std::string name;
        RGBA ambient; // Ambient color for the material
        RGBA difuse; // Diffuse color for the material
        RGBA specular; // Optional: Specular color for highlights
        float shininess; // Optional: Shininess factor for specular highlights
        float disolve; // Optional: Dissolve factor for transparency or other effects
        int8_t illum; // Optional: Illumination model (e.g., 0 for color on and ambient off, 1 for color on and ambient on, etc.)
    public:
        Material();
        Material(std::string name, RGBA ambient, RGBA difuse, RGBA specular, float shininess = 0.0f, float disolve = 1.0f, int8_t illum = 2);
        const std::string getName() const;
        const RGBA getAmbient() const;
        const RGBA getDifuse() const;
        const RGBA getSpecular() const;
        float getShininess() const;
        float getDissolve() const;
        int8_t getIllum() const;
        void setName(std::string name);
        void setAmbient(RGBA ka);
        void setDifuse(RGBA kd);
        void setSpecular(RGBA ks);
        void setShininess(float shininess);
        void setDissolve(float disolve);
        void setIllum(int8_t illum);
};