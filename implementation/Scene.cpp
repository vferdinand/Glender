#include "../hpp/Scene.hpp"

Scene::Scene(const std::string filePathObj){//}, const std::string filePathMtl){
    Loader loader(filePathObj);
    vertices = loader.getVertices();
    triangles = loader.getTriangles();

    normals = loader.getNormals();
    materials = loader.getMaterials();
    camera.generate_rays();
    kdtree = new KDTree(triangles, vertices);
}

// Wandelt eine Liste von Hitpoints in ein Bild (Image) um
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

    // Schleife über alle Pixel des Bildes
    for(uint16_t i = 0; i < height; i++){
        for(uint16_t j = 0; j < width; j++){
            // Standardfarbe: transparent schwarz
            RGBA col = {0.0, 0.0, 0.0, 0.0};

            // Berechnung des Index im Hitpoints-Vektor (Zeilenweise Speicherung)
            uint32_t index = i * width + j;

            // Prüfen, ob der Index im Bereich liegt und der Hitpoint gültig ist
            if (index < hitpoints.size() && 
                hitpoints.at(index).getDistance() != std::numeric_limits<float>::max()) {
                
                // Farbe aus dem Farbarray anhand des Farbindex des getroffenen Dreiecks setzen

                //col = colors.at(hitpoints.at(index).getTriangle()->getColorIndex());

                
                
                
                //Parameter vordefinieren
                const Triangle* tri = hitpoints.at(index).getTriangle();
                Vector3D n = tri->getNormalIndex();
                Vector3D lightDirection = {1,1,1};

                //Material holen
                Material m = materials.at(tri->getMaterialIndex());

                //Globaler Lichtvektor
                light.setGlobalLightVec(lightDirection);

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
                col = diffuse + ambient + specular;

            }

            // Farbe im Bild an der Position (i,j) setzen
            image.set(i, j, col);
        }
    }

    // Das fertige Bild zurückgeben
    return image;
}

// kombiniert Scenen-Funktionalität
Image Scene::generateImage() {
    std::vector<Ray> rays = camera.get_rays();
    return transformHitpointsToImage(calculateHitpointsBruteForce(rays));
}

// Ändern der Kameraparameter
void Scene::setCamera(const Point3D& eyePos, const Vector3D& viewDir, float pixelWidth, float pixelHeight, int horizontalPixels, int verticalPixels) {
    camera.set_everything(eyePos, viewDir, pixelWidth, pixelHeight, horizontalPixels, verticalPixels);
    camera.generate_rays();
}

std::vector<Hitpoint> Scene::calculateHitpointsKDTree(std::vector<Ray>& rays) {
    std::cout << "Rays size: " << rays.size() << std::endl;
    std::vector<Hitpoint> hitpoints;
    const float EPS = 1e-6f;

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

std::vector<Hitpoint> Scene::calculateHitpointsBruteForce(std::vector<Ray>& rays) {
    std::cout << "Rays size: " << rays.size() << std::endl;
    std::vector<Hitpoint> hitpoints;
    const float EPS = 1e-6f;
    
    for (auto& ray : rays) {
        // Ursprungspunkt des Strahls
        Point3D orig_p = ray.getOrigin();
        // Richtungsvektor des Strahls
        Vector3D dir_v = ray.getDirection();

        // Umwandlung in Eigen Vektoren zur Berechnung
        Eigen::Vector3f orig(orig_p.x, orig_p.y, orig_p.z);
        Eigen::Vector3f dir(dir_v.x, dir_v.y, dir_v.z);

        Hitpoint hp;  // Zwischenspeicher für den nächsten Hitpoint

        for (const auto& tri : triangles) {
            // Indizes der Dreiecksecken
            const auto& idx = tri.getIndices();

            // Positionen der Dreiecksecken als Eigen-Vektoren
            Eigen::Vector3f b(vertices[idx[1]].x, vertices[idx[1]].y, vertices[idx[1]].z);
            Eigen::Vector3f a(vertices[idx[0]].x, vertices[idx[0]].y, vertices[idx[0]].z);
            Eigen::Vector3f c(vertices[idx[2]].x, vertices[idx[2]].y, vertices[idx[2]].z);

            // Kanten des Dreiecks berechnen
            Eigen::Vector3f edge1 = b - a;
            Eigen::Vector3f edge2 = c - a;

            // Kreuzprodukt aus Strahlrichtung und zweiter Dreieckskante
            Eigen::Vector3f pvec = dir.cross(edge2);

            // Determinante des Gleichungssystems (zeigt Parallelität an)
            float det = edge1.dot(pvec);

            // Wenn Determinante nahe null ist, sind Strahl und Dreieck parallel → kein Schnitt
            if (std::abs(det) < EPS)
                continue;

            // Inverse der Determinante
            float invDet = 1.0f / det;

            // Vektor vom Dreieckseck a zum Strahlursprung
            Eigen::Vector3f tvec = orig - a;

            // Berechnung des baryzentrischen Koordinaten u
            float u = tvec.dot(pvec) * invDet;
            if (u < 0.0f || u > 1.0f)
                continue; // Schnittpunkt liegt außerhalb des Dreiecks

            // Kreuzprodukt von tvec und edge1
            Eigen::Vector3f qvec = tvec.cross(edge1);

            // Berechnung des baryzentrischen Koordinaten v
            float v = dir.dot(qvec) * invDet;
            if (v < 0.0f || (u + v) > 1.0f)
                continue; // Schnittpunkt liegt außerhalb des Dreiecks

            // Berechnung des Parameters t auf dem Strahl (Entfernung vom Ursprung)
            float t = edge2.dot(qvec) * invDet;
            if (t <= EPS)
                continue; // Schnittpunkt liegt hinter dem Strahlursprung oder zu nah

            // Berechnung des exakten Schnittpunkts im 3D-Raum
            Eigen::Vector3f hitPos = orig + dir * t;

            Hitpoint hp_tmp;
            Point3D p = { hitPos.x(), hitPos.y(), hitPos.z() };

            // Setzen der Hitpoint-Parameter
            hp_tmp.setPosition(p);
            hp_tmp.setDistance(t);
            hp_tmp.setTriangle(&tri);

            // Speichere nur den nächstgelegenen Hitpoint
            if (hp_tmp.getDistance() < hp.getDistance()) {
                hp = hp_tmp;
            }
        }
        hitpoints.push_back(hp);
    }

    return hitpoints;
}


