#include "../hpp/Camera.hpp"
#include <cmath>

/**
 * @brief Normalisiert einen Vektor, sodass er die Länge 1 hat.
 * Falls der Eingabevektor die Länge 0 hat, wird ein Standardvektor (0, 0, 1) zurückgegeben.
 * 
 * @param v Der zu normalisierende Vektor
 * @return Der normalisierte Vektor oder (0, 0, 1) falls v die Länge 0 hat
 */
Vector3D Camera::normalize(const Vector3D& v) {
    float len = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (len > 0.0f) ? v/len : Vector3D(0, 0, 1);
}
/**
 * @brief das Kreuzprodukt zweier Vektoren.
 * 
 * @param a Erster Vektor
 * @param b Zweiter Vektor
 * @return Das Kreuzprodukt a × b
 */
Vector3D Camera::cross(const Vector3D& a, const Vector3D& b) {
    return Vector3D(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,  
        a.x * b.y - a.y * b.x
    );
}

/**
 * @brief den Strahl (Ray), der durch das Pixel an Position (x,y) geht.
 * Der Strahl startet im Kamerapunkt (eye) und verläuft durch die Mitte des angegebenen Pixels.
 * 
 * @param x X-Koordinate des Pixels 
 * @param y Y-Koordinate des Pixels 
 * @return Der berechnete Strahl
 */
Ray Camera::calculate_ray ( u_int32_t x , u_int32_t y ) const {
    //calculate basevectors 
    Vector3D forward = normalize(view);
    Vector3D right = normalize(cross(Vector3D{0, 1, 0}, forward));
    Vector3D up = cross(forward, right); 

    //pixelsize
    float pixel_width = width / widthPixels;
    float pixel_height = height / lengthPixels;

     //left-right | top-down-scan
    float u = (x + 0.5f) * pixel_width - (width / 2.0f);
    float v = (height / 2.0f) - (y + 0.5f) * pixel_height;

    //calculate raydirection
    Point3D pixel_pos = eye + (forward + right * u + up * v);
    Vector3D direction = normalize(pixel_pos - eye);

    return Ray(eye, direction);
}

/**
 * @brief Strahlen für alle Pixel des Bildes.
 * Die Strahlen werden zeilenweise von oben nach unten und von links nach rechts generiert.
 */
void Camera::generate_rays() {
    rays.clear();
    rays.reserve(get_width_pixels() * get_length_pixels());

    for (u_int16_t y = 0; y < get_length_pixels(); ++y) {
        for (u_int16_t x = 0; x < get_width_pixels(); ++x) {
            rays.push_back(calculate_ray(x, y));
        }
    }
}

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
void Camera::set_everything(const Point3D& eyePos, const Vector3D& viewDir, float pixelWidth, float pixelHeight, u_int16_t horizontalPixels, u_int16_t verticalPixels) {
    eye = eyePos;
    view = viewDir;
    width = pixelWidth;
    height = pixelHeight;
    widthPixels = horizontalPixels;
    lengthPixels = verticalPixels;
}

const std::vector<Ray>& Camera::get_rays() const {
    return rays;
}

Point3D Camera::get_eye() const {
    return eye;
}

Vector3D Camera::get_view() const {
    return view;
}

float Camera::get_width() const {
    return width;
}

float Camera::get_height() const {
    return height;
}

u_int8_t Camera::get_width_pixels() const {
    return widthPixels;
}

u_int8_t Camera::get_length_pixels() const {
    return lengthPixels;
}