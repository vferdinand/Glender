#include "../hpp/Hitpoint.hpp"

Hitpoint::Hitpoint(){}

const Point3D Hitpoint::getPosition() {
    return position;
}
const float Hitpoint::getDistance() {
    return distance;
}
const Triangle* Hitpoint::getTriangle() {
    return triangle;
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