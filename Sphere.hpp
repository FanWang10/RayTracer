#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <math.h>
#include "Ray.hpp"
#include "Material.hpp"
#include <iostream>
class Sphere
{
    glm::vec3 center;
    float radius;
    Material * matP;

    public:
        Sphere(){}
        Sphere(glm::vec3 c, float r, Material * m) : center(c), radius(r), matP(m) {}
        bool hit(Ray & r, float tMin, float tMax, HitRecord & rec)
        {
            glm::vec3 oc = r.getOrigin() - center;
            float a = glm::dot(r.getDirection(), r.getDirection());
            float b = 2 * glm::dot(r.getDirection(), oc);
            float c = glm::dot(oc, oc) - radius * radius;
            float d = b * b - 4 * a * c;
            if(d < 0.0f)
            {
                return false;
            }
            else{
                float t = (-b - sqrt(d)) / (2 * a);
                if(t < tMin || t > tMax)
                {   
                    return false;
                } else {
                rec.t = t;
                rec.hitPoint = r.at(t);
                rec.normal = glm::normalize(rec.hitPoint - center);
                rec.matP = matP;
                return true;
            }
    }
    
}
};


#endif