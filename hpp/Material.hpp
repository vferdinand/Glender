#pragma once

#include "Structs.hpp"

class Material {
    private:
        std::string name;
        RGBA ka;
        RGBA kd;
        RGBA ks;
    public:
        Material(std::string name, RGBA ka, RGBA kd, RGBA ks);
        const std::string getName() const;
        const RGBA getKa() const;
        const RGBA getKd() const;
        const RGBA getKs() const;
        void setName(std::string name);
        void setKa(RGBA ka);
        void setKd(RGBA kd);
        void setKs(RGBA ks);
};