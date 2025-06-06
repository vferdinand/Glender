#pragma once

#include "Ray.hpp"
#include "Structs.hpp"

#include <vector>
#include <cmath>

class Camera {
    
    private: 
        Point3D eye;
        Vector3D view;
        
        float width;
        float height;

        u_int16_t widthPixels;
        u_int16_t lengthPixels;

        std::vector<Ray> rays;

        static Vector3D normalize(const Vector3D& v);
        static Vector3D cross(const Vector3D& a, const Vector3D& b);
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
        void set_everything(const Point3D& eyePos, const Vector3D& viewDir, float pixelWidth, float pixelHeight, u_int16_t horizontalPixels, u_int16_t verticalPixels);
        void generate_rays();
        const std::vector<Ray>& get_rays() const;
        Point3D get_eye() const;
        Vector3D get_view() const;
        float get_width() const;
        float get_height() const;
        u_int16_t get_width_pixels() const;
        u_int16_t get_length_pixels() const;
        
};