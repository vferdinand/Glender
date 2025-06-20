#include "../hpp/Camera.hpp"

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

void Camera::set_everything(const Point3D& eyePos, const Vector3D& viewDir, float pixelWidth, float pixelHeight, u_int16_t horizontalPixels, u_int16_t verticalPixels) {
    eye = eyePos;
    view = viewDir;
    width = pixelWidth;
    height = pixelHeight;
    widthPixels = horizontalPixels;
    lengthPixels = verticalPixels;
}

void Camera::setScaling(const Point3D& eyePos, const Vector3D& viewDir, float scalingFactor, int resolutionFactor) {
    const u_int8_t baseWidth = 160;
    const u_int8_t baseHeight = 90;

    uint16_t horizontalPixels = baseWidth * resolutionFactor;
    uint16_t verticalPixels = baseHeight * resolutionFactor;

    
    float pixelWidth  = scalingFactor * 1.0;
    float pixelHeight = pixelWidth * 9.0f / 16.0f;
    

    set_everything(eyePos, viewDir, pixelWidth, pixelHeight, horizontalPixels, verticalPixels);
}

Ray Camera::get_ray(uint32_t x, uint32_t y) const {
    return calculate_ray(x, y);
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

u_int16_t Camera::get_width_pixels() const {
    return widthPixels;
}

u_int16_t Camera::get_length_pixels() const {
    return lengthPixels;
}