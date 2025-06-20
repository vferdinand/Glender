#pragma once

#include "Ray.hpp"
#include <vector>

class Camera {
    
    private: 
        Point3D eye;
        Vector3D view;
  
        float width;
        float height;

        u_int16_t widthPixels;
        u_int16_t lengthPixels;

        std::vector<Ray> rays;

        void setScaling(float width, float height);

        
        /**
         * @brief Normalisiert einen Vektor, sodass er die Länge 1 hat.
         * Falls der Eingabevektor die Länge 0 hat, wird ein Standardvektor (0, 0, 1) zurückgegeben.
         * 
         * @param v Der zu normalisierende Vektor
         * @return Der normalisierte Vektor oder (0, 0, 1) falls v die Länge 0 hat
         */
        static Vector3D normalize(const Vector3D& v);
        
        /**
         * @brief das Kreuzprodukt zweier Vektoren.
         * 
         * @param a Erster Vektor
         * @param b Zweiter Vektor
         * @return Das Kreuzprodukt a × b
         */
        static Vector3D cross(const Vector3D& a, const Vector3D& b);
        
        /**
         * @brief den Strahl (Ray), der durch das Pixel an Position (x,y) geht.
         * Der Strahl startet im Kamerapunkt (eye) und verläuft durch die Mitte des angegebenen Pixels.
         * 
         * @param x X-Koordinate des Pixels 
         * @param y Y-Koordinate des Pixels 
         * @return Der berechnete Strahl
         */
        Ray calculate_ray(u_int32_t x, u_int32_t y) const;
    
    public:
        Camera(const Point3D& eyePos = Point3D(-2.4, -2.4, -2.4), 
           const Vector3D& viewDir = Vector3D(1, 1, 1), 
           float pixelWidth = 1.0f, 
           float pixelHeight = 1.0f, 
           u_int16_t horizontalPixels = 40,
           u_int16_t verticalPixels = 40)
        : eye(eyePos), 
          view(viewDir), 
          width(pixelWidth),
          height(pixelHeight),
          widthPixels(horizontalPixels),
          lengthPixels(verticalPixels)  
          {}

        /**
         * @brief Strahlen für alle Pixel des Bildes.
         * Die Strahlen werden zeilenweise von oben nach unten und von links nach rechts generiert.
         */
        /*void Camera::generate_rays() {
            rays.clear();
            rays.reserve(get_width_pixels() * get_length_pixels());
            for (u_int16_t y = 0; y < get_length_pixels(); ++y) {
                for (u_int16_t x = 0; x < get_width_pixels(); ++x) {
                    rays.push_back(calculate_ray(x, y));
                }
            }
        }*/

        /**
         * @brief Settet Parameter neu.
         * 
         * @param eyePos Ausgangsposition der Kamera
         * @param viewDir Ausrichtung der Kamera
         * @param pixelWidth Breite eines Pixels
         * @param pixelHeight Höhe eines Pixels
         * @param horizontalPixels Anzahl der Pixel in der Horizontale
         * @param verticalPixels Anzahl der Pixel in der Vertikale
         */
        void set_everything(const Point3D& eyePos, const Vector3D& viewDir, float pixelWidth, float pixelHeight, u_int16_t horizontalPixels, u_int16_t verticalPixels);
        void setScaling(const Point3D& eyePos, const Vector3D& viewDir, float scalingFactor, int resolutionFactor);
        void setWithScaling(const Point3D& eyePos, const Vector3D& viewDir, int scaleFactor);
        Ray get_ray(uint32_t x, uint32_t y) const;
        const std::vector<Ray>& get_rays() const;
        Point3D get_eye() const;
        Vector3D get_view() const;
        float get_width() const;
        float get_height() const;
        u_int16_t get_width_pixels() const;
        u_int16_t get_length_pixels() const;
        
};