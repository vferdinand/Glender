#include "../hpp/Ray.hpp"

/**
 * @brief Standardkonstruktor für einen Ray.
 * 
 * Erstellt einen Strahl mit Ursprung im Koordinatenursprung (0,0,0) 
 * und Richtung entlang der z-Achse (0,0,1).
 */
Ray::Ray() : origin(0,0,0), direction(0,0,1) {}

/**
 * @brief Konstruktor mit benutzerdefiniertem Ursprung und Richtung.
 * 
 * @param o Ursprungspunkt des Strahls.
 * @param d Richtungsvektor des Strahls.
 */
Ray::Ray(const Point3D& o, const Vector3D& d) : origin(o), direction(d) {}

/**
 * @brief Kreuzprodukt zweier Vektoren berechnen.
 * 
 * @param a Erster Vektor.
 * @param b Zweiter Vektor.
 * @return Kreuzprodukt von a und b.
 */
Vector3D Ray::cross(const Vector3D& a, const Vector3D& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
/**
 * @brief Skalarprodukt (Dot-Produkt) zweier Vektoren berechnen.
 * 
 * @param a Erster Vektor.
 * @param b Zweiter Vektor.
 * @return Skalarprodukt von a und b.
 */
float Ray::dot(const Vector3D& a, const Vector3D& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
 * @brief Prüft den Schnitt eines Strahls mit einem Dreieck mittels Möller-Trumbore-Algorithmus.
 * 
 * Falls ein Schnittpunkt gefunden wird, wird dieser in den übergebenen Hitpoint geschrieben.
 * 
 * @param ray Der zu prüfende Strahl.
 * @param v0 Erstes Eckpunkt des Dreiecks.
 * @param v1 Zweites Eckpunkt des Dreiecks.
 * @param v2 Drittes Eckpunkt des Dreiecks.
 * @param hit Referenz auf ein Hitpoint-Objekt, in das bei Treffer der Schnittpunkt geschrieben wird.
 * @return true, wenn ein Schnitt vorliegt; sonst false.
 */
bool Ray::rayTriangleIntersect(const Ray& ray, const Vertex& v0, const Vertex& v1, const Vertex& v2, Hitpoint& hit) const {
    static const float EPSILON = 1e-6f;

    Vector3D edge1 = {
        v1.x - v0.x,
        v1.y - v0.y,
        v1.z - v0.z
    };
    Vector3D edge2 = {
        v2.x - v0.x,
        v2.y - v0.y,
        v2.z - v0.z
    };

    Vector3D h = Ray::cross(this->direction, edge2);
    float a = Ray::dot(edge1, h);
    if (std::abs(a) < EPSILON) return false;  // Parallel

    float f = 1.0f / a;
    Vector3D s = {
        this->origin.x - v0.x,
        this->origin.y - v0.y,
        this->origin.z - v0.z
    };
    
    float u = f * dot(s, h);
    if (u < 0.0f || u > 1.0f) return false;

    Vector3D q = cross(s, edge1);
    float v = f * dot(ray.getDirection(), q);
    if (v < 0.0f || (u + v) > 1.0f) return false;

    float t = f * dot(edge2, q);
    if (t > EPSILON) {
        hit.setDistance(t);
        hit.setPosition(ray.getOrigin() + ray.getDirection() * t);
        return true;
    }

    return false;
}

const Point3D& Ray::getOrigin() const{
    return origin;
}
const Vector3D& Ray::getDirection() const{
    return direction;
}