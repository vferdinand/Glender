#include "../hpp/AABB.hpp"

/**
 * @class AABB
 * @brief Achsenparallele Bounding Box zur räumlichen Partitionierung.
 *
 * Wird verwendet, um Ray-Triangle-Intersektionen durch hierarchische Raumaufteilung effizienter zu machen.
 */

/**
 * @brief Konstruktor: Erstellt eine leere AABB mit unendlichen Grenzen.
 *
 * Initialisiert das Minimum auf +∞ und das Maximum auf -∞, damit `expand()` diese beim ersten Aufruf korrekt einschränken kann.
 */
AABB::AABB() {
    float inf = std::numeric_limits<float>::infinity();
    min = { inf, inf, inf };
    max = { -inf, -inf, -inf };
}

/**
 * @brief Erweitert die Bounding Box so, dass sie alle übergebenen Punkte einschließt.
 *
 * @param indices Eine Liste von Indizes, die auf Vertizes in `vertices` zeigen.
 * @param vertices Die vollständige Liste aller Vertices im Raum.
 */
void AABB::expand(const std::vector<unsigned int>& indices, const std::vector<Vertex>& vertices) {
    for (unsigned int i : indices) {
        const auto& v = vertices[i];
        min.x = std::min(min.x, v.x);
        min.y = std::min(min.y, v.y);
        min.z = std::min(min.z, v.z);

        max.x = std::max(max.x, v.x);
        max.y = std::max(max.y, v.y);
        max.z = std::max(max.z, v.z);
    }
}

/**
 * @brief Prüft, ob ein Strahl (Ray) die Bounding Box schneidet.
 *
 * Verwendet das sogenannte "Slab-Verfahren", um den Schnitt in allen drei Raumachsen zu testen.
 *
 * @param ray Der Ray, der auf die AABB getestet wird.
 * @return true, wenn der Ray die AABB schneidet, andernfalls false.
 */
bool AABB::intersect(const Ray& ray) const {
    float tmin = -std::numeric_limits<float>::infinity();
    float tmax = std::numeric_limits<float>::infinity();

    const Point3D& orig = ray.getOrigin();
    const Vector3D& dir = ray.getDirection();

    for (int i = 0; i < 3; ++i) {
        float minVal, maxVal, origVal, dirVal;
        if (i == 0) {
            minVal = min.x; maxVal = max.x; origVal = orig.x; dirVal = dir.x;
        } else if (i == 1) {
            minVal = min.y; maxVal = max.y; origVal = orig.y; dirVal = dir.y;
        } else {
            minVal = min.z; maxVal = max.z; origVal = orig.z; dirVal = dir.z;
        }

    float invD = 1.0f / dirVal;
    float t0 = (minVal - origVal) * invD;
    float t1 = (maxVal - origVal) * invD;
    if (invD < 0.0f) std::swap(t0, t1);

    tmin = std::max(tmin, t0);
    tmax = std::min(tmax, t1);

    if (tmax < tmin) {
        return false;
        }
    }
    return true;
}
