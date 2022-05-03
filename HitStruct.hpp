#ifndef HITSTRUCT_HPP
#define HITSTRUCT_HPP

#include "Ray.hpp" 

class Material;

struct HitRecord
{
    public:
        float t;
        glm::vec3 hitPoint;
        glm::vec3 normal;
        Material * matP;
};


#endif