#pragma once
#include "Structs.hpp"


class Light {

    private: 
        
        Vector3D globalLightVec;

    public: 

       RGBA initLight();
       void setGlobalLightVec(Vector3D v);

};