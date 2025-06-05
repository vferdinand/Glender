#pragma once
#include "Structs.hpp"


class Light {

    private: 
        
        Vector3D globalLightVec;
        RGBA color;

    public: 

       void setGlobalLightVec(Vector3D v);
       RGBA getLightColor();

};