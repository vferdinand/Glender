#pragma once

#include "Ray.hpp"
#include "Structs.hpp"
#include "Ray.hpp"

class Camera {
    
    private: 
        Point3D eye;
        Vector3D view;

        float width;
        float height;

        int widthPixels;
        int lengthPixels;

    public:
        Camera();
        
        Vector3D get_pixel(int x, int y) const;
        Ray get_ray(int x, int y) const ;

        static Vector3D normalize(const Vector3D& v);
        static Vector3D cross(const Vector3D& a, const Vector3D& b);
        Point3D get_eye() const;
        Vector3D get_view() const;
        float get_width() const;
        float get_height() const;
        int get_width_pixels() const;
        int get_length_pixels() const;
        void initialize(const Point3D& eye_pos, 
                   const Vector3D& view_dir,
                   float img_width, 
                   float img_height,
                   int pixel_width, 
                   int pixel_length);
};