#pragma once

#include "Structs.hpp"
#include "Hitpoint.hpp"
#include <optional>


class Ray {
    private:
        Point3D origin;
        Vector3D direction;

        /**
         * @brief Skalarprodukt (Dot-Produkt) zweier Vektoren berechnen.
         * 
         * @param a Erster Vektor.
         * @param b Zweiter Vektor.
         * @return Skalarprodukt von a und b.
         */
        static float dot(const Vector3D& a, const Vector3D& b);
        
        /**
         * @brief Kreuzprodukt zweier Vektoren berechnen.
         * 
         * @param a Erster Vektor.
         * @param b Zweiter Vektor.
         * @return Kreuzprodukt von a und b.
         */
        static Vector3D cross(const Vector3D& a, const Vector3D& b);
    public:

        /**
         * @brief Standardkonstruktor für einen Ray.
         * 
         * Erstellt einen Strahl mit Ursprung im Koordinatenursprung (0,0,0) 
         * und Richtung entlang der z-Achse (0,0,1).
         */
        Ray();

        /**
         * @brief Konstruktor mit benutzerdefiniertem Ursprung und Richtung.
         * 
         * @param o Ursprungspunkt des Strahls.
         * @param d Richtungsvektor des Strahls.
         */
        Ray(const Point3D & o, const Vector3D& d);


        const Point3D& getOrigin() const;
        const Vector3D& getDirection() const;
        
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
        bool rayTriangleIntersect(const Ray& ray, const Vertex& a, const Vertex& b, const Vertex& c, Hitpoint& hit) const;
};