#include "Ray.hpp"
#include "Vector3D"


class Camera {
    
    private: 
        Vector3D eye;
        Vector3D view;

        float with;
        float height;

        int widthPixels;
        int lengthPixels;

    public:
        Vector3D get_pixel(int x, int y) const;
        Ray get_ray(int x, int y) const ;

}