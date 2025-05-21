#pragma once

#include "Ray.hpp"
#include "Structs.hpp"
#include <vector>

class Camera {
    
    private: 
        //Orts & Richtungsvektor die Standpunkt der Kamera & Blickrichtung repräsentieren
        Point3D eye;
        Vector3D view;
        

        float width;
        float height;

        int widthPixels;
        int lengthPixels;

        //Vektor der alle generierten Strahlen enthält
        std::vector<Ray> rays;
    public:
        /**
         * Konstruktor.
         * 
         * @param eyePos Ausgangsposition der Kamera
         * @param viewDir Ausrichtung der Kamera
         * @param pixelWidth Breite eines Pixels
         * @param pixelHeight Höhe eines Pixels
         * @param horizontalPixels Anzahl der Pixel in der Horizontale
         * @param verticalPixels Anzahl der Pixel in der Vertikale
         */
        Camera(const Point3D& eyePos = Point3D(-2.4, -2.4, -2.4), 
           const Vector3D& viewDir = Vector3D(1, 1, 1), 
           float pixelWidth = 1.0f, 
           float pixelHeight = 1.0f, 
           int horizontalPixels = 40,
           int verticalPixels = 40)
        : eye(eyePos), 
          view(viewDir), 
          width(pixelWidth),
          height(pixelHeight),
          widthPixels(horizontalPixels),
          lengthPixels(verticalPixels)  
          {}
       
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
         * Der Strahl startet im Kamerapunkt (eye) und verläuft durch die Mitte des angegebenen Pixels.
         * 
         * @param x X-Koordinate des Pixels 
         * @param y Y-Koordinate des Pixels 
         * @return Der berechnete Strahl
         */
        Ray calculate_ray(int x, int y) const ;

        /**
         * Generiert Strahlen für alle Pixel des Bildes.
         * Die Strahlen werden zeilenweise von oben nach unten und von links nach rechts generiert.
         * 
         * @return Vektor mit allen generierten Strahlen
         */
        void generate_rays();
        const std::vector<Ray>& get_rays() const;
        Point3D get_eye() const;
        Vector3D get_view() const;
        float get_width() const;
        float get_height() const;
        int get_width_pixels() const;
        int get_length_pixels() const;
        void set_everything(const Point3D& eyePos, const Vector3D& viewDir, float pixelWidth, float pixelHeight, int horizontalPixels, int verticalPixels);
};