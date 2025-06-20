#pragma once

struct KDPrim {
    const Triangle* tri;
    const std::vector<Vertex>* vertices;

    Vertex centroid() const {
        const auto& vtx = *vertices;
        const auto& idx = tri->getIndices();
        return {
            (vtx[idx[0]].x + vtx[idx[1]].x + vtx[idx[2]].x) / 3.0f,
            (vtx[idx[0]].y + vtx[idx[1]].y + vtx[idx[2]].y) / 3.0f,
            (vtx[idx[0]].z + vtx[idx[1]].z + vtx[idx[2]].z) / 3.0f
        };
    }
};