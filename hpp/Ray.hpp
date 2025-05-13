#pragma once

#include "Structs.hpp"

class Ray {
    private:
        Point3D origin;
        Vector3D direction;
    public:
        Ray();
        Ray(const Point3D & o, const Vector3D& d);
        const Point3D& getOrigin() const;
        const Vector3D& getDirection() const;
};