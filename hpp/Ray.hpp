#ifndef RAY_H
#define RAY_H

#include "Structs.hpp"

class Ray {
    private:
        Point3D origin;
        Vector3D direction;
    public:
        const Point3D getOrigin() const;
        const Vector3D getVector3D() const;
};

#endif