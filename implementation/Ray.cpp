#include "../hpp/Ray.hpp"

Ray::Ray(){}

const Point3D Ray::getOrigin() const{
    return origin;
}
const Vector3D Ray::getVector3D() const{
    return direction;
}