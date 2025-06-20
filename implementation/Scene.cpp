#include "../hpp/Scene.hpp"


Scene::Scene(const std::string filePathObj){//}, const std::string filePathMtl){
    Loader loader(filePathObj);
    vertices = loader.getVertices();
    triangles = loader.getTriangles();

    normals = loader.getNormals();
    materials = loader.getMaterials();
    kdtree = new KDTree(triangles, vertices);
    light = Light(Vector3D(1.0f, 1.0f, 1.0f), RGBA{1.0, 1.0, 1.0, 1.0});
}

Image Scene::generateImage() {
    uint16_t width = camera.get_width_pixels();
    uint16_t height = camera.get_length_pixels();
    Image image(height, width);

    for (uint16_t y = 0; y < height; ++y) {
        for (uint16_t x = 0; x < width; ++x) {
            Ray ray = camera.get_ray(x, y);  // Ray wird on-demand berechnet
            Hitpoint hp;
            if (kdtree->intersect(ray, hp)) {
                // Beleuchtung berechnen (wie in transformHitpointsToImage)
                RGBA col = computeShading(hp).clamp();  // Extrahiere die Beleuchtungslogik
                image.set(y, x, col);
            } else {
                image.set(y, x, {0.1, 0.1, 0.2, 0.1});  // Hintergrundfarbe
            }
        }
    }
    return image;
}

// Hilfsfunktion für Beleuchtung (aus transformHitpointsToImage extrahiert)
RGBA Scene::computeShading(Hitpoint& hp) {
    const Triangle* tri = hp.getTriangle();
    Material m = materials.at(tri->getMaterialIndex());
    Vector3D N = normals[tri->getNormalIndex()].normalized();
    Vector3D L = light.getGlobalLightVec().normalized();  // Lichtrichtung
    //Vector3D E = camera.get_view().normalized();
    Vector3D E = (camera.get_eye() - hp.getPosition()).normalized();
    Vector3D R = (-L).reflected(N);

    float diffuseFactor = std::max(0.0f, N.dot(L));
    float specFactor = std::pow(std::max(0.0f, R.dot(E)), m.getShininess());

    RGBA diffuse = m.getDifuse() * diffuseFactor;
    RGBA ambient = (m.getAmbient() * light.getLightColor()) * 0.05; // Ambient-Beleuchtung, hier mit einem festen Faktor
    RGBA specular = m.getSpecular() * specFactor * RGBA{1.0, 1.0, 1.0};

    switch (m.getIllum()) {
        case 0:
            return diffuse;
        case 1:
            return diffuse + ambient;
        case 2:
            return diffuse + ambient + specular;
        default:
            return diffuse + ambient + specular;
    }
}


std::vector<Hitpoint> Scene::calculateHitpoints(std::vector<Ray>& rays) {
    std::vector<Hitpoint> hitpoints;

    for (auto& ray : rays) {
        Hitpoint hp;
        if (kdtree->intersect(ray, hp)) {
            hitpoints.push_back(hp);
        } else {
            hitpoints.push_back(Hitpoint());
        }
    }

    return hitpoints;
}


void Scene::setCamera(const Point3D& eyePos, const Vector3D& viewDir, float pixelWidth, float pixelHeight, int horizontalPixels, int verticalPixels) {
    camera.set_everything(eyePos, viewDir, pixelWidth, pixelHeight, horizontalPixels, verticalPixels);
}

void Scene::setCamera(const Point3D& eyePos, const Vector3D& viewDir, float scalingFactor, int resolutionFactor) {
    camera.setScaling(eyePos, viewDir, scalingFactor, resolutionFactor);
}

void Scene::setLight(const Vector3D& lightDir) {
    light.setGlobalLightVec(lightDir.normalized());
}