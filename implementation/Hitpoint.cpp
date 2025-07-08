#include "../hpp/Hitpoint.hpp"

Hitpoint::Hitpoint(){}

Point3D Hitpoint::getPosition() {
    return position;
}

Vector3D Hitpoint::getNormal() {
    return normal;
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

void Hitpoint::setNormal(const Vector3D& nor) {
    normal = nor;
}

void Hitpoint::setDistance(float d) {
    distance = d;
}

void Hitpoint::setTriangle(const Triangle* tri) {
    triangle = tri;
}