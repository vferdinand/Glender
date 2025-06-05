#include "../hpp/Light.hpp"

void Light::setGlobalLightVec(Vector3D v) {
    globalLightVec = v;
}

RGBA Light::getLightColor() {
    return color;
}