#pragma once
#include "Structs.hpp"
#include "Ray.hpp"
#include <algorithm>

struct AABB {
    Vertex min;
    Vertex max;

    AABB() {
        min = { std::numeric_limits<float>::max(),
                std::numeric_limits<float>::max(),
                std::numeric_limits<float>::max() };

        max = { std::numeric_limits<float>::lowest(),
                std::numeric_limits<float>::lowest(),
                std::numeric_limits<float>::lowest() };
    }

    void expand(const std::vector<uint32_t>& indices, const std::vector<Vertex>& vertices) {
        for (uint32_t idx : indices) {
            const Vertex& v = vertices[idx];
            min.x = std::min(min.x, v.x);
            min.y = std::min(min.y, v.y);
            min.z = std::min(min.z, v.z);
            max.x = std::max(max.x, v.x);
            max.y = std::max(max.y, v.y);
            max.z = std::max(max.z, v.z);
        }
    }

    bool intersect(const Ray& ray) const {
        // Simple slab intersection
        float tmin = (min.x - ray.getOrigin().x) / ray.getDirection().x;
        float tmax = (max.x - ray.getOrigin().x) / ray.getDirection().x;
        if (tmin > tmax) std::swap(tmin, tmax);

        float tymin = (min.y - ray.getOrigin().y) / ray.getDirection().y;
        float tymax = (max.y - ray.getOrigin().y) / ray.getDirection().y;
        if (tymin > tymax) std::swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax)) return false;

        if (tymin > tmin) tmin = tymin;
        if (tymax < tmax) tmax = tymax;

        float tzmin = (min.z - ray.getOrigin().z) / ray.getDirection().z;
        float tzmax = (max.z - ray.getOrigin().z) / ray.getDirection().z;
        if (tzmin > tzmax) std::swap(tzmin, tzmax);

        if ((tmin > tzmax) || (tzmin > tmax)) return false;

        return true;
    }
};
