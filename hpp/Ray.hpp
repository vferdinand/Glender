#pragma once

#include "Structs.hpp"
#include <optional>
#include "Hitpoint.hpp"


class Ray {
    private:
        Point3D origin;
        Vector3D direction;

        static float dot(const Vector3D& a, const Vector3D& b);
        static Vector3D cross(const Vector3D& a, const Vector3D& b);
    public:
        Ray();
        Ray(const Point3D & o, const Vector3D& d);
        const Point3D& getOrigin() const;
        const Vector3D& getDirection() const;
        bool rayTriangleIntersect(const Ray& ray, const Vertex& a, const Vertex& b, const Vertex& c, Hitpoint& hit) const;
};