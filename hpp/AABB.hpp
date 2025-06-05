#pragma once
#include "Structs.hpp"
#include "Ray.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>  // nur temporär zum Debugge

struct AABB {
    Point3D min;
    Point3D max;

    AABB();

    void expand(const std::vector<unsigned int>& indices, const std::vector<Vertex>& vertices);
    bool intersect(const Ray& ray) const;
};