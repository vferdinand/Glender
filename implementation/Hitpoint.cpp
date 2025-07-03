#include "../hpp/Hitpoint.hpp"

Hitpoint::Hitpoint(){}

Point3D Hitpoint::getPosition() {
    return position;
}
float Hitpoint::getDistance() {
    return distance;
}
const Triangle* Hitpoint::getTriangle() const {
    return triangle;
}

float Hitpoint::getT() const {
    return t;
}

void Hitpoint::setT(float newT) {
    t = newT;
}

void Hitpoint::setPosition(const Point3D& pos) {
    position = pos;
}

void Hitpoint::setDistance(float d) {
    distance = d;
}

void Hitpoint::setTriangle(const Triangle* tri) {
    triangle = tri;
}

float Hitpoint::getU() const {
    return u;
}

void Hitpoint::setU(float newU) {
    u = newU;
}

float Hitpoint::getV() const {
    return v;
}

void Hitpoint::setV(float newV) {
    v = newV;
}