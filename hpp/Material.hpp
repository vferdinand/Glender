#pragma once

#include "structs/RGBA.hpp"

class Material {
    private:
        float reflectionFactor;
        std::string name;
        RGBA ambient; // Ambient color for the material
        RGBA difuse; // Diffuse color for the material
        RGBA specular; // Optional: Specular color for highlights
        float shininess; // Optional: Shininess factor for specular highlights
        float disolve; // Optional: Dissolve factor for transparency or other effects
        int8_t illum; // Optional: Illumination model (e.g., 0 for color on and ambient off, 1 for color on and ambient on, etc.)
        float transparency = 0.0f;
        float ior =1.0f; //index of refraction
        u_int8_t diffuseTex;
    public:
        Material();
        Material(std::string name, RGBA ambient, RGBA difuse, RGBA specular, float shininess = 8.0f, float disolve = 1.0f, int8_t illum = 2, float reflectionsFactor = 0.0f);
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
        void setReflectionFactor(float reflectionFactor);
        float getReflectionFactor() const;
        void setTransparency(float kt);
        void setIOR(float ni);
        float getTransparency() const;
        float getIOR() const;
        void setDiffuseTex(u_int8_t diffuseTex);
        u_int8_t getDiffuseTex();
};