#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>

class Ray
{
    private:
        glm::vec3 origin;
        glm::vec3 direction;
    public:
        Ray()
        : origin{0.0f, 0.0f, 0.0f},
          direction{0.0f, 0.0f, 0.0f}
        {}

        Ray(glm::vec3 o, glm::vec3 d)
        : origin(o),
          direction(d)
        {}

        glm::vec3 getOrigin()
        {
            return origin;
        }

        glm::vec3 getDirection()
        {
            return direction;
        }


        glm::vec3 at(float tP)
        {
            return origin + tP * direction;
        }


};

#endif