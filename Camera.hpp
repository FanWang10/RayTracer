#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Ray.hpp"
#include <math.h>

glm::vec3 randomUnitDisk()
{
    return glm::normalize(glm::vec3((drand48() * 2.0f - 1.0f), (drand48() * 2.0f - 1.0f), 0));
}
class Camera 
{
    private:
        glm::vec3 position;
        glm::vec3 horizontal;
        glm::vec3 vertical;
        glm::vec3 lowerLeftCornor;
        glm::vec3 u, v, w;
        float vfovd;
        float lensRadius;


    public:
        Camera()
        : position{0.0f, 0.0f, 0.0f},
          horizontal{0.0f, 0.0f, 0.0f},
          vertical{0.0f, 0.0f, 0.0f},
          lowerLeftCornor{0.0f, 0.0f, 0.0f}
        {}

        Camera(glm::vec3 p, glm::vec3 h, glm::vec3 ve, float vd, glm::vec3 lookAt, glm::vec3 vUp, float aspectRatio, float aperture, float focusDist)
        :position(p),
        horizontal(h),
        vertical(ve),
        vfovd(vd)
        {
            // degree to radian 
            float vfovr = ( vd * M_PI ) / 180.0f;
            float ratio = tan(vfovr / 2);
            horizontal = ratio * horizontal;
            vertical = ratio * vertical;

            // rotate camera;
            w = glm::normalize(position - lookAt);
            u = glm::normalize(glm::cross(vUp, w));
            v = glm::normalize(glm::cross(w, u));
            horizontal = u * horizontal * focusDist;
            vertical = v * vertical * focusDist;
            
            lowerLeftCornor = position - 0.5f * horizontal - 0.5f * vertical - focusDist * w;
            lensRadius = aperture / 2.0f;
        }

        Ray getRay(float s, float t)
        {
            glm::vec3 rd = lensRadius * randomUnitDisk();
            glm::vec3 offset = u * rd.x + v * rd.y;

            return Ray(position + offset, lowerLeftCornor + s * horizontal + t * vertical - position - offset);
        }

};




#endif