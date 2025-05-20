#include "../hpp/Camera.hpp"
#include <cmath>

//Camera::Camera(): width(5), height(5), widthPixels(10),lengthPixels(10) {}

void Camera::initialize(const Point3D& eye_pos, const Vector3D& view_dir, float width, float height, int pixel_width, int pixel_length) {
    eye = eye_pos; 
    view = view_dir;    
    this->width = width;
    this->height = height;
    widthPixels = pixel_width;
    lengthPixels = pixel_length;
}

Vector3D Camera::normalize(const Vector3D& v) {
    float len = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (len > 0.0f) ? v/len : Vector3D(0, 0, 1);
}

Vector3D Camera::cross(const Vector3D& a, const Vector3D& b) {
    return Vector3D(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,  
        a.x * b.y - a.y * b.x
    );
}

Ray Camera::calculate_ray ( int x , int y ) const {
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

std::vector<Ray> Camera::generate_rays() const {
    std::vector<Ray> rays;
    rays.reserve(get_width_pixels() * get_length_pixels());

    for (int y = 0; y < get_length_pixels(); ++y) {
        for (int x = 0; x < get_width_pixels(); ++x) {
            rays.push_back(calculate_ray(x, y));
        }
    }
    return rays;
}

std::vector<Ray>& Camera::get_rays() {
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

int Camera::get_width_pixels() const {
    return widthPixels;
}

int Camera::get_length_pixels() const {
    return lengthPixels;
}
