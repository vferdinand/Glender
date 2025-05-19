#include "../hpp/Scene.hpp"

Image Scene::transformHitpointsToImage(std::vector<std::vector<Hitpoint>> hitpoints){
    size_t height = hitpoints.size();
    size_t width = hitpoints.at(0).size();

    Image image(height, width);

    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            RGBA col = {0.0, 0.0, 0.0, 0.0};
            if(hitpoints.at(i).at(j).getDistance() != std::numeric_limits<float>::max()){
                col = colors.at(hitpoints.at(i).at(j).getTriangle()->getColorIndex());
            }
            image.set(i, j, col);
        }
    }

    return image;
}

void Scene::addTriangle(Triangle tri) {
    triangles.push_back(std::move(tri));
}

const std::vector<Triangle>& Scene::getTriangles() const {
    return triangles;
}