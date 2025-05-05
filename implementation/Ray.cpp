#include "../hpp/Ray.hpp"

Ray::Ray(){}

const Point3D Ray::getOrigin(){
    return origin;
}
const Vector3D Ray::getVector3D(){
    return direction;
}