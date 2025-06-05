#include "../hpp/KDTree.hpp"

KDTree::KDTree(const std::vector<Triangle>& triangles, const std::vector<Vertex>& verts)
    : vertices(&verts), triangleStorage(triangles) {
    std::vector<KDPrim> prims;
    for (const Triangle& t : triangleStorage)
        prims.push_back({ &t, &verts });
    root = build(prims, 0);
}

KDTree::~KDTree() {
    delete root;
}

KDNode::~KDNode() {
    delete left;
    delete right;
}

KDNode* KDTree::build(std::vector<KDPrim>& prims, int depth) {
    KDNode* node = new KDNode();

    for (const auto& p : prims)
        node->bbox.expand(p.tri->getIndices(), *vertices);

    if (prims.size() <= 2 || depth > 20) {
        for (const auto& p : prims)
            node->tris.push_back(p.tri);
        return node;
    }

    int axis = depth % 3;
    std::sort(prims.begin(), prims.end(), [axis](const KDPrim& a, const KDPrim& b) {
        return a.centroid()[axis] < b.centroid()[axis];
    });

    size_t mid = prims.size() / 2;
    std::vector<KDPrim> left(prims.begin(), prims.begin() + mid);
    std::vector<KDPrim> right(prims.begin() + mid, prims.end());

    node->axis = axis;
    node->splitPos = prims[mid].centroid()[axis];
    node->left = build(left, depth + 1);
    node->right = build(right, depth + 1);

    return node;
}

bool KDTree::intersect(const Ray& ray, Hitpoint& hit) const {
    return intersectNode(root, ray, hit);
}

bool KDTree::intersectNode(const KDNode* node, const Ray& ray, Hitpoint& hit) const {
    if (!node->bbox.intersect(ray)) return false;
    bool found = false;

    if (node->isLeaf()) {
        for (const Triangle* tri : node->tris) {
            const auto& idx = tri->getIndices();
            const Vertex& a = (*vertices)[idx[0]];
            const Vertex& b = (*vertices)[idx[1]];
            const Vertex& c = (*vertices)[idx[2]];

            if (ray.rayTriangleIntersect(ray, a, b, c, hit)) {
                hit.setTriangle(tri);
                found = true;
            }
        }
        return found;
    }   

    bool leftHit = intersectNode(node->left, ray, hit);
    bool rightHit = intersectNode(node->right, ray, hit);
    return leftHit || rightHit;
}