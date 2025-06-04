#pragma once
#include "Triangle.hpp"
#include "Structs.hpp"
#include "Ray.hpp"
#include "Hitpoint.hpp"
#include "KDPrim.hpp"
#include "KDNode.hpp"
#include <vector>
#include <algorithm>

class KDTree {
private:
    KDNode* root;
    const std::vector<Vertex>* vertices;

    KDNode* build(std::vector<KDPrim>& prims, int depth);
    bool intersectNode(const KDNode* node, const Ray& ray, Hitpoint& hit) const;
public:
    ~KDTree();
    KDTree(const std::vector<Triangle>& triangles, const std::vector<Vertex>& vertices);
    bool intersect(const Ray& ray, Hitpoint& hit) const;
};
