#include "../hpp/Scene.hpp"

Scene::Scene(const std::string filePathObj, const std::string filePathMtl){
    Loader loader;
    loader.loadOBJ(filePathObj, filePathMtl);
    vertices = loader.getVertices();
    triangles = loader.getTriangles();
    colors = loader.getColors();
    camera.initialize(Point3D{0, 0, 0}, Vector3D {1, -2, 1}, 2.0f, 2.0f, 5, 5);
}

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

Image Scene::transformHitpointsToImage(std::vector<Hitpoint> hitpoints, size_t height, size_t width){
    Image image(height, width);

    for(size_t i = 0; i < height; i++){
        for(size_t j = 0; j < width; j++){
            RGBA col = {0.0, 0.0, 0.0, 0.0};
            if(hitpoints.at(i*height + j).getDistance() != std::numeric_limits<float>::max()){
                col = colors.at(hitpoints.at(i*height + j).getTriangle()->getColorIndex());
            }
            image.set(i, j, col);
        }
    }

    return image;
}


const std::vector<Triangle>& Scene::getTriangles() const {
    return triangles;
}

Image Scene::generateImage() {

    //convertHitpointsToImage(calculateHitpoints());
}

std::vector<Hitpoint> Scene::calculateHitpoints(std::vector<Ray>& rays) {
           
    std::vector<Hitpoint> hitpoints;
    const float EPS = 1e-6f;

    for (auto& ray : rays) {
        //Startpunkt des Strahls
        Point3D orig_p = ray.getOrigin();
        //Richtung des Strahls
        Vector3D dir_v = ray.getDirection();

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