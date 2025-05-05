#pragma once

#include "Structs.hpp"

class Ray {
    private:
        Point3D origin;
        Vector3D direction;
    public:
        Ray();
        const Point3D getOrigin();
        const Vector3D getVector3D();
};