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

// Rekursive Shading-Funktion mit Spiegelung (und optional Transparenz)
RGBA Scene::computeShading(Hitpoint& hp, int depth) {
    if (depth <= 0) return RGBA{0, 0, 0, 1}; // Rekursionstiefe erreicht

    const Triangle* tri = hp.getTriangle();
    Material m = materials.at(tri->getMaterialIndex());
    Vector3D N = normals[tri->getNormalIndex()].normalized();
    Vector3D L = light.getGlobalLightVec().normalized();
    Vector3D E = (camera.get_eye() - hp.getPosition()).normalized();
    Vector3D R = (-L).reflected(N);

    float diffuseFactor = std::max(0.0f, N.dot(L));
    float specFactor = std::pow(std::max(0.0f, R.dot(E)), m.getShininess());

    RGBA diffuse = m.getDifuse() * diffuseFactor;
    RGBA ambient = (m.getAmbient() * light.getLightColor()) * 0.05f;
    RGBA specular = m.getSpecular() * specFactor * RGBA{1.0, 1.0, 1.0};

    RGBA color = diffuse + ambient + specular;

    // Spiegelung (reflektierend)
    if (m.getIllum() == 3 || m.getIllum() == 5) { // illum==3 oder 5: Spiegelnd (nach OBJ-Standard)
        Vector3D viewDir = (camera.get_eye() - hp.getPosition()).normalized();
        Vector3D reflectDir = viewDir.reflected(N).normalized();
        Ray reflectRay(hp.getPosition() + reflectDir * 1e-4f, reflectDir);

        Hitpoint reflectHit;
        if (kdtree->intersect(reflectRay, reflectHit)) {
            RGBA reflectedColor = computeShading(reflectHit, depth - 1);
            float kr = m.getSpecular().r; // Anteil der Spiegelung (kann auch Mittelwert aus RGBA sein)
            color = color * (1.0f - kr) + reflectedColor * kr;
        }
    }

    if (m.getDissolve() < 1.0f || m.getIllum() == 4 || m.getIllum() == 6) {
        float etaI = 1.0f; // Air
        float etaT = m.getShininess(); // Material's index of refraction
        Vector3D I = (hp.getPosition() - camera.get_eye()).normalized();
        Vector3D T = refract(I, N, etaI, etaT); // Snell's law

        Ray refrRay(hp.getPosition() + T * 1e-4f, T);
        Hitpoint refrHit;
        RGBA refrColor = RGBA{0,0,0,1};
        if (kdtree->intersect(refrRay, refrHit)) {
            refrColor = computeShading(refrHit, depth-1);
        }
        // Mix local color and refracted color
        float alpha = m.getDissolve();
        color = color * alpha + refrColor * (1.0f - alpha);
    }

    return color.clamp();
}

Vector3D Scene::refract(const Vector3D& I, const Vector3D& N, float etaI, float etaT) {
    float cosi = std::clamp(I.dot(N), -1.0f, 1.0f);
    float etai = etaI, etat = etaT;
    Vector3D n = N;
    if (cosi < 0) { cosi = -cosi; }
    else { std::swap(etai, etat); n = -N; }
    float etaRatio = etai / etat;
    float k = 1 - etaRatio * etaRatio * (1 - cosi * cosi);
    if (k < 0)
        return Vector3D(0,0,0); // Total internal reflection
    else
        return I * etaRatio + n * (etaRatio * cosi - std::sqrt(k));
}

// Wrapper für alten Code (ohne Rekursionstiefe)
RGBA Scene::computeShading(Hitpoint& hp) {
    return computeShading(hp, 4); // z.B. Rekursionstiefe 4
}


/*
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
*/

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