#include "../hpp/Light.hpp"


Light::Light(Vector3D globalLightVec, RGBA color){
    this->globalLightVec = globalLightVec;
    this->color = color;
}

void Light::setGlobalLightVec(Vector3D v) {
    globalLightVec = v;
}

Vector3D Light::getGlobalLightVec() {
    return globalLightVec;
}

RGBA Light::getLightColor() {
    return color;
}