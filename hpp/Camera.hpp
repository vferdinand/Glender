#pragma once

#include "Ray.hpp"
#include "Structs.hpp"
#include <vector>

class Camera {
    
    private: 
        //Orts & Richtungsvektor die Standpunkt der Kamera & Blickrichtung repräsentieren
        Point3D eye;
        Vector3D view;
        
        //Höhe und Breite eines Pixels
        float width;
        float height;

        //Anzahl der Pixel auf horizontaler/ vertikaler Ebene
        int widthPixels;
        int lengthPixels;

        //Vektor der alle generierten Strahlen enthält
        std::vector<Ray> rays;
    public:

        /**
         * Initialisiert die Position der Kamera(Camera) und ich welche Richtung diese schaut.
         * 
         * @param eye_pos Ortsvektor der Kamera
         * @param view_dir Blickrichtung der Kamera
         * @param width Breite eines einzelnen Pixels
         * @param height Höhe eines einzelnen Pixels
         * @param pixel_width Anzahl der Pixel in der horizontalen Ebene
         * @param pixel_height Anzahl der Pixeln in der vertikalen Ebene        
        */
        void initialize(const Point3D& eye_pos, const Vector3D& view_dir, float width, float height, int pixel_width, int pixel_length);
       
        /**
         * Normalisiert einen Vektor, sodass er die Länge 1 hat.
         * Falls der Eingabevektor die Länge 0 hat, wird ein Standardvektor (0, 0, 1) zurückgegeben.
         * 
         * @param v Der zu normalisierende Vektor
         * @return Der normalisierte Vektor oder (0, 0, 1) falls v die Länge 0 hat
         */
        static Vector3D normalize(const Vector3D& v);

        /**
         * Berechnet das Kreuzprodukt zweier Vektoren.
         * 
         * @param a Erster Vektor
         * @param b Zweiter Vektor
         * @return Das Kreuzprodukt a × b
        */
        static Vector3D cross(const Vector3D& a, const Vector3D& b);

        /**
         * Berechnet den Strahl (Ray), der durch das Pixel an Position (x,y) geht.
         * Der Strahl startet im Kamerapunkt (eye) und geht durch die Mitte des angegebenen Pixels.
         * 
         * @param x X-Koordinate des Pixels (von links nach rechts)
         * @param y Y-Koordinate des Pixels (von oben nach unten)
         * @return Der berechnete Strahl
         */
        Ray calculate_ray(int x, int y) const ;

        /**
         * Generiert Strahlen für alle Pixel des Bildes.
         * Die Strahlen werden zeilenweise von oben nach unten und von links nach rechts generiert.
         * 
         * @return Vektor mit allen generierten Strahlen
         */
        std::vector<Ray> generate_rays() const;

        std::vector<Ray>& get_rays();
        Point3D get_eye() const;
        Vector3D get_view() const;
        float get_width() const;
        float get_height() const;
        int get_width_pixels() const;
        int get_length_pixels() const;
};