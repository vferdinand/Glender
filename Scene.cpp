#include "Scene.hpp"

void Scene::addTriangle(Triangle tri) {
    triangles.push_back(std::move(tri));
}

const std::vector<Triangle>& Scene::getTriangles() const {
    return triangles;
}