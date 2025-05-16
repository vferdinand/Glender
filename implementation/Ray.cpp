#include "../hpp/Ray.hpp"

Ray::Ray() : origin(0,0,0), direction(0,0,1) {}

Ray::Ray(const Point3D& o, const Vector3D& d) : origin(o), direction(d) {}

const Point3D& Ray::getOrigin() const{
    return origin;
}
const Vector3D& Ray::getDirection() const{
    return direction;
}