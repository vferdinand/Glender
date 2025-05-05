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
