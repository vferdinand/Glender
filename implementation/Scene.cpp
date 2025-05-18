#include "../hpp/Scene.hpp"

void Scene::addTriangle(Triangle tri) {
    triangles.push_back(std::move(tri));
}

const std::vector<Triangle>& Scene::getTriangles() const {
    return triangles;
}

Image Scene::generateImage() {
    convertHitpointsToImage(calculateHitpoints());
}

std::vector<Hitpoint> Scene::calculateHitpoints(std::vector<Ray>& rays, std::vector<Triangle>& triangles, std::vector<Vertex>& vertices) {
    
    /*for (const auto& ray : rays) {
        for (const auto& triangle : triangles) {
            std::vector<uint32_t> indices = triangle.getIndices();
            Vertex a = vertices.at(indices.at(0));
            Vertex b = vertices.at(indices.at(1));
            Vertex c = vertices.at(indices.at(2));
    */
           
           
    std::vector<Hitpoint> hitpoints;
    const float EPS = 1e-6f;

    for (const auto& ray : rays) {
        // Ray‐Origin und ‐Direction in Eigen‐Vektoren
        Eigen::Vector3f orig(ray.origin.x, ray.origin.y, ray.origin.z);
        Eigen::Vector3f dir(ray.direction.x, ray.direction.y, ray.direction.z);

        for (const auto& tri : triangles) {
            auto idx = tri.getIndices();
            const auto& A = vertices[idx[0]].position;
            const auto& B = vertices[idx[1]].position;
            const auto& C = vertices[idx[2]].position;

            Eigen::Vector3f a(A.x, A.y, A.z);
            Eigen::Vector3f b(B.x, B.y, B.z);
            Eigen::Vector3f c(C.x, C.y, C.z);

            // Möller–Trumbore
            Eigen::Vector3f edge1 = b - a;
            Eigen::Vector3f edge2 = c - a;
            Eigen::Vector3f pvec  = dir.cross(edge2);
            float det = edge1.dot(pvec);
            if (std::abs(det) < EPS) 
                continue;

            float invDet = 1.0f / det;
            Eigen::Vector3f tvec = orig - a;
            float u = tvec.dot(pvec) * invDet;
            if (u < 0.0f || u > 1.0f) 
                continue;

            Eigen::Vector3f qvec = tvec.cross(edge1);
            float v = dir.dot(qvec) * invDet;
            if (v < 0.0f || u + v > 1.0f) 
                continue;

            float t = edge2.dot(qvec) * invDet;
            if (t <= EPS) 
                continue;

            // Treffer!
            Point3D intersection {
                orig.x() + dir.x() * t,
                orig.y() + dir.y() * t,
                orig.z() + dir.z() * t
            };
            Hitpoint hp;
            hp.position = intersection;
            hp.distance = t;
            hp.triangle = &tri;
            hitpoints.push_back(hp);
            }
        }
    }

    return hitpoints;
}

Image Scene::convertHitpointsToImage(std::vector<Hitpoint> hitpoints) {
    //aus gefundenen Hitpoints werden getroffene Dreiecke rausgefiltert
    //dann in Pixeln angezeigt --> Speichern in Image-Objekt
    
}

