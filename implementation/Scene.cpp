#include "../hpp/Scene.hpp"


Scene::Scene(const std::string filePathObj){//}, const std::string filePathMtl){
    Loader loader(filePathObj);
    vertices = loader.getVertices();
    triangles = loader.getTriangles();

    normals = loader.getNormals();
    materials = loader.getMaterials();
    //camera.generate_rays();
    kdtree = new KDTree(triangles, vertices);
    light = Light(Vector3D(1.0f, 1.0f, 1.0f), RGBA{1.0, 1.0, 1.0, 1.0});
}

Image Scene::transformHitpointsToImage(std::vector<Hitpoint> hitpoints) {
    // Wenn keine Hitpoints vorhanden sind, gebe ein leeres Bild zurück
    if(hitpoints.size() == 0){
        return Image(0, 0);
    }

    // Breite und Höhe des Bildes basieren auf den Kameraeigenschaften
    uint16_t width = camera.get_width_pixels();
    uint16_t height = camera.get_length_pixels();

    // Neues Bild mit den Maßen Höhe x Breite erstellen
    Image image(height, width);
    std::cout << "Image size: " << width << "x" << height << std::endl;
    std::cout << "Hitpoints size: " << hitpoints.size() << std::endl;
    // Schleife über alle Pixel des Bildes
    Vector3D lightDirection = light.getGlobalLightVec();//{1.0,1.0,1.0};
    for(uint16_t i = 0; i < height; i++){
        for(uint16_t j = 0; j < width; j++){

            // Standardfarbe: transparent schwarz
            RGBA col = {0.0, 0.0, 0.0, 0.0};

            // Berechnung des Index im Hitpoints-Vektor (Zeilenweise Speicherung)
            uint32_t index = i * width + j;

            // Prüfen, ob der Index im Bereich liegt und der Hitpoint gültig ist
            if (index < hitpoints.size() && 
                hitpoints.at(index).getDistance() != std::numeric_limits<float>::max()) {
                
                //Parameter vordefinieren
                const Triangle* tri = hitpoints.at(index).getTriangle();
                Vector3D n = tri->getNormalIndex();

                //Material holen
                Material m = materials.at(tri->getMaterialIndex());

                //Globaler Lichtvektor
                //light.setGlobalLightVec(lightDirection);

                //Difuse Beleuchtung
                RGBA c = m.getDifuse();
                
                //Glanzfaktor
                float shininess = m.getShininess();

                //Abiente-Beleuchtung -> vom Material abhängig
                RGBA ka = m.getAmbient();

                //Grundbeleuchtung
                RGBA ca = light.getLightColor();
                
                //Lichtfarbe
                RGBA c_light = {1.0,1.0,1.0};

                //Spekular-Koeffizienten
                RGBA ks = m.getSpecular();
                
                /// Normalisieren der Vektoren nur einmal
                Vector3D N = n.normalized();
                Vector3D L = lightDirection.normalized();
                Vector3D E = camera.get_view().normalized();
                Vector3D R = (-L).reflected(N);

                // Diffuser Faktor (Lambert)
                float diffuseFactor = std::max(0.0f, N.dot(L));

                // Spekularer Faktor (Phong)
                float specFactor = std::pow(std::max(0.0f, R.dot(E)), shininess);

                // Farben berechnen
                RGBA diffuse = c * diffuseFactor;
                RGBA ambient = ka * ca;
                RGBA specular = ks * specFactor * c_light;

                // Endfarbe zusammensetzen
                col = specular; //diffuse + ambient;
                std::cout << "jo" << std::endl;
            }

            // Farbe im Bild an der Position (i,j) setzen
            image.set(i, j, col);
        }
    }

    // Das fertige Bild zurückgeben
    return image;
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
    //camera.generate_rays();
}

void Scene::setCamera(const Point3D& eyePos, const Vector3D& viewDir, float scalingFactor, int resolutionFactor) {
    camera.setScaling(eyePos, viewDir, scalingFactor, resolutionFactor);
}
