#pragma once
#include "../Triangle.hpp"
#include "AABB.hpp"
#include <vector>

struct KDNode {
    AABB bbox;
    KDNode* left = nullptr;
    KDNode* right = nullptr;
    int axis = 0;
    float splitPos = 0.0f;
    std::vector<const Triangle*> tris;

    bool isLeaf() const { return left == nullptr && right == nullptr; }

    /**
     * @brief Destruktor für einen KDNode.
     *
     * Löscht rekursiv alle Kindknoten.
     */
    ~KDNode();
};