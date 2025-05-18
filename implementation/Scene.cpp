#include "../hpp/Scene.hpp"

void Scene::addTriangle(Triangle tri) {
    triangles.push_back(std::move(tri));
}

const std::vector<Triangle>& Scene::getTriangles() const {
    return triangles;
}

Image Scene::generateImage() {
    //convertHitpointsToImage(calculateHitpoints());
}

std::vector<Hitpoint> Scene::calculateHitpoints(std::vector<Ray>& rays, std::vector<Triangle>& triangles, std::vector<Vertex>& vertices) {
           
    std::vector<Hitpoint> hitpoints;
    const float EPS = 1e-6f;

    for (auto& ray : rays) {
        //Startpunkt des Strahls
        Point3D orig_p = ray.getOrigin();
        //Richtung des Strahls
        Vector3D dir_v = ray.getVector3D();

        Eigen::Vector3f orig(orig_p.x, orig_p.y, orig_p.z);
        Eigen::Vector3f dir(dir_v.x, dir_v.y, dir_v.z);


        for (const auto& tri : triangles) {
            const auto& idx = tri.getIndices();
            Eigen::Vector3f b(vertices[idx[1]].x, vertices[idx[1]].y, vertices[idx[1]].z);
            Eigen::Vector3f a(vertices[idx[0]].x, vertices[idx[0]].y, vertices[idx[0]].z);
            Eigen::Vector3f c(vertices[idx[2]].x, vertices[idx[2]].y, vertices[idx[2]].z);

            Eigen::Vector3f edge1 = b - a;
            Eigen::Vector3f edge2 = c - a;
            Eigen::Vector3f pvec = dir.cross(edge2);
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
            if (v < 0.0f || (u + v) > 1.0f)
                continue;

            float t = edge2.dot(qvec) * invDet;
            if (t <= EPS)
                continue;

            Eigen::Vector3f hitPos = orig + dir * t;
            Hitpoint hp;
            Point3D p = { hitPos.x(), hitPos.y(), hitPos.z() };
            hp.setPosition(p);
            hp.setDistance(t);
            hp.setTriangle(&tri);
            hitpoints.push_back(hp);
            
        }
    }
    return hitpoints;
}

Image Scene::convertHitpointsToImage(std::vector<Hitpoint> hitpoints) {
    //aus gefundenen Hitpoints werden getroffene Dreiecke rausgefiltert
    //dann in Pixeln angezeigt --> Speichern in Image-Objekt
    
}

