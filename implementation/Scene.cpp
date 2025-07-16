#include "../hpp/Scene.hpp"


Scene::Scene(const std::string filePathObj){
    Loader loader(filePathObj);
    vertices = loader.getVertices();
    triangles = loader.getTriangles();
    texture_coord = loader.getTextureCoords();
    textures = loader.getTextures();
    normals = loader.getNormals();
    materials = loader.getMaterials();
    kdtree = new KDTree(triangles, vertices);
    light = Light(Vector3D(1.0f, 1.0f, 1.0f), RGBA{5.0, 5.0, 5.0, 1.0});
}

Image Scene::generateImage() {
    uint16_t width = camera.get_width_pixels();
    uint16_t height = camera.get_length_pixels();
    Image image(height, width);

    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads > 2) num_threads -= 2;

    ThreadPool pool(num_threads);
    std::vector<std::future<void>> futures;
        for (uint16_t y = 0; y < height; ++y) {
            futures.push_back(pool.enqueue([&image, this, y, width]() {
            for (uint16_t x = 0; x < width; ++x) {
                Ray ray = camera.get_ray(x, y);
                Hitpoint hp;
                if (kdtree->intersect(ray, hp)) {
                    RGBA col = computeShading(hp, ray, 0).clamp();
                    image.set(y, x, col);
                } else {
                    image.set(y, x, {0.1, 0.1, 0.2, 0.1});
                }
            }
        }));
    }

    for (auto& f : futures) {
        f.get();
    }
    return image;
}
    
RGBA Scene::computeShading( Hitpoint& hp, const Ray& ray, int depth) {
    
    const Triangle* tri = hp.getTriangle();
    Material m = materials.at(tri->getMaterialIndex());
    Vector3D N = computeInterpolatedNormal(hp);
    Vector3D L = light.getGlobalLightVec().normalized(); 

    Vector3D E = (camera.get_eye() - hp.getPosition()).normalized();
    Vector3D H = (L + E).normalized();

    float diffuseFactor = std::max(0.0f, N.dot(L));
    float specFactor = std::pow(std::max(0.0f, H.dot(E)), m.getShininess());

    uint8_t maxDepth = 3;
    
    RGBA diffuse = m.getDifuse() * diffuseFactor;
    RGBA ambient = (m.getAmbient() * light.getLightColor()) * 0.01;
    RGBA specular = m.getSpecular() * specFactor * RGBA{1.0, 1.0, 1.0};

    if (tri->getTextureIndices().size() == 3) {
        diffuse = textureInterpolation(hp, tri->getTextureIndices(), m) * diffuseFactor;
    }

    RGBA localColor = ambient + diffuse + specular;

    float kr = m.getReflectionFactor();
    if (kr > 0.0f && depth < maxDepth) {
        Vector3D reflectedDir = (-ray.getDirection()).reflect(hp.getNormal());
        Ray reflectedRay(hp.getPosition() + reflectedDir * 1e-4f, reflectedDir);

        Hitpoint hp2;
        if (kdtree->intersect(reflectedRay, hp2)) {
            RGBA reflectedColor = computeShading(hp2, reflectedRay, depth + 1);
            localColor = localColor * (1 - kr) + reflectedColor * kr;

            return reflectedColor;
        } 
    }
    float kt = m.getTransparency();
    if (kt > 0.0f && depth < maxDepth) {
        Vector3D refractedDir;
        if (refract(ray.getDirection(), N, m.getIOR(), refractedDir)) {
            Ray refractedRay(hp.getPosition() + refractedDir * 1e-4f, refractedDir);
            Hitpoint hpRefr;
            if (kdtree->intersect(refractedRay, hpRefr)) {
                RGBA refractedColor = computeShading(hpRefr, refractedRay, depth + 1);
                localColor = localColor * (1 - kt) + refractedColor * kt;
            }
        }
    }
    return localColor; 

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

Vector3D Scene::computeInterpolatedNormal(Hitpoint hp) {
    const Triangle* tri = hp.getTriangle();
    if (!tri) return Vector3D(0.0f, 0.0f, 1.0f);  

    std::array<uint32_t, 3> normalIndices = tri->getNormalIndices();
    uint32_t ni0 = normalIndices[0];
    uint32_t ni1 = normalIndices[1];
    uint32_t ni2 = normalIndices[2];

    Vector3D n0 = normals[ni0];
    Vector3D n1 = normals[ni1];
    Vector3D n2 = normals[ni2];

    float u = hp.getU();
    float v = hp.getV();
    float w = 1.0f - u - v;

    Vector3D interpolated = (n0 * w + n1 * u + n2 * v).normalized();

    return interpolated;
}

RGBA Scene::textureInterpolation(Hitpoint& hp, const std::vector<uint32_t>& textureIndices, Material& m) {

    float u = hp.getU();
    float v = hp.getV();
    float w = 1.0f - u - v;

    Vector3D uv0 = texture_coord[textureIndices.at(0)];
    Vector3D uv1 = texture_coord[textureIndices.at(1)];
    Vector3D uv2 = texture_coord[textureIndices.at(2)];

    Vector3D uv = uv0 * w + uv1 * u + uv2 * v;

    return textures.at(m.getDiffuseTex()).sample(uv);
}

bool Scene::refract(const Vector3D& I, const Vector3D& N, float eta, Vector3D& refracted) const {
    float cosi = std::clamp(I.dot(N), -1.0f, 1.0f);

    float etai = 1.0f, etat = eta;
    Vector3D n = N;

    if (cosi < 0) {
        cosi = -cosi;
    } else {
        std::swap(etai, etat);
        n = -N;
    }

    float etaRatio = etai / etat;
    float k = 1 - etaRatio * etaRatio * (1 - cosi * cosi);

    if (k < 0) return false;

    refracted = I * etaRatio + n * (etaRatio * cosi - std::sqrt(k));
    return true;
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
