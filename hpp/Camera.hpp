#include "Ray.hpp"
#include "Vector3D.hpp"


class Camera {
    
    private: 
        Vector3D eye;
        Vector3D view;

        float with;
        float height;

        int widthPixels;
        int lengthPixels;

    public:

        Camera();
        Vector3D get_pixel(int x, int y) const;
        Ray get_ray(int x, int y) const ;

        Vector3D get_eye() const;
        Vector3D get_view() const;
        float get_width() const;
        float get_height() const;
        int get_width_pixels() const;
        int get_length_pixels() const;
        
}