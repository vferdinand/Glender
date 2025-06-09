#pragma once
#include "Structs.hpp"


class Light {

    private: 
        Vector3D globalLightVec;
        RGBA color;

    public: 
        Light(Vector3D globalLightVec = Vector3D(1.0f, 1.0f, 1.0f), RGBA color = {1.0f, 1.0f, 1.0f, 1.0f});
        void setGlobalLightVec(Vector3D v);
        Vector3D getGlobalLightVec();
        RGBA getLightColor();

};