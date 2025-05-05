#include "../hpp/Camera.hpp"

Camera::Camera(){}


Vector3D Camera::get_pixel ( int x , int y ) const {
    // noch zu schreiben
    return Vector3D();
}
Ray Camera::get_ray ( int x , int y ) const {
   // noch zu schreiben
    return Ray();
}
Vector3D Camera::get_eye() const {
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