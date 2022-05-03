#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "HitStruct.hpp"
#include <math.h>
glm::vec3 reflect(glm::vec3 & v, glm::vec3 & normal)
{
    return v - 2 * glm::dot(v, normal) * normal;
}

glm::vec3 refract(glm::vec3 & in, glm::vec3 & normal, float etaRatio)
{
    glm::vec3 outV = etaRatio * (in + normal * (glm::dot(-1.0f * in, normal) / (glm::length(in) * glm::length(normal))));
    glm::vec3 outH = -1 * sqrt(1 - (glm::length(outV) * glm::length(outV))) * normal;
    return outV + outH;
}

float schlickReflectance(float cos, float rid)
{
    float r0 = (1-rid) / (1+rid);
    r0 = r0 * r0;
    return r0 + (1-r0) * pow((1-cos), 5);
}

class Material
{
    public:
    virtual bool sendNewRay(Ray & r, HitRecord & hr, glm::vec3 & changed, Ray & newRay) const = 0;
};

class Lambertian : public Material
{
    private:
    glm::vec3 baseColor;


    public:
    Lambertian(glm::vec3 color) : baseColor(color) {}
    virtual bool sendNewRay(Ray & r, HitRecord & hr, glm::vec3 & changed, Ray & newRay) const
    {
        glm::vec3 tempNewRay = hr.normal + glm::normalize(glm::vec3((drand48() * 2.0f - 1.0f), (drand48() * 2.0f - 1.0f), (drand48() * 2.0f - 1.0f)));
        
        // avoid the new ray point into the object
        float threshold = 1e-7;

        if((tempNewRay.x < threshold) && (tempNewRay.y < threshold) && (tempNewRay.z < threshold))
        {
            tempNewRay = hr.normal;
        }

        newRay = Ray(hr.hitPoint, tempNewRay);
        
        changed = baseColor;
        
        return true;
    }

};

class Metal : public Material
{
    private:
    glm::vec3 baseColor;
    float fuzz = 0.0f;

    public:
    Metal(glm::vec3 color) : baseColor(color) {}

    virtual bool sendNewRay(Ray & r, HitRecord & hr, glm::vec3 & changed, Ray & newRay) const
    {
        glm::vec3 reflectedDirection = reflect(glm::normalize(r.getDirection()), hr.normal) + fuzz * glm::normalize(glm::vec3((drand48() * 2.0f - 1.0f), (drand48() * 2.0f - 1.0f), (drand48() * 2.0f - 1.0f)));
        
        newRay = Ray(hr.hitPoint, reflectedDirection);
        
        changed = baseColor;
        
        return (glm::dot(newRay.getDirection(), hr.normal) > 0);
    }

};

class Dielectrics: public Material
{
    private:
    float ir;

    public:
    Dielectrics(double indexOfRefraction) : ir(indexOfRefraction) {}

    virtual bool sendNewRay(Ray & r, HitRecord & hr, glm::vec3 & changed, Ray & newRay) const
    {
        changed = glm::vec3(1.0f, 1.0f, 1.0f);
        float refractRatio;
        if(glm::dot(r.getDirection(), hr.normal) < 0)
        {
            refractRatio = (1.0f / ir);
        }else
        {
            refractRatio = ir;
        }

        glm::vec3 rayDirectNormalized = glm::normalize(r.getDirection());

        
        float cos = dot(-rayDirectNormalized, glm::normalize(hr.normal)) > 1.0f ? 1.0f :  dot(-rayDirectNormalized, glm::normalize(hr.normal));
        float sin = sqrt(1 - cos * cos);

        bool noRefract = (refractRatio * sin) > 1.0f;
        glm::vec3 dir;

        if(noRefract || schlickReflectance(cos, refractRatio) > drand48())
        {
            dir = reflect(rayDirectNormalized, hr.normal);
        }
        else
        {
            dir = refract(rayDirectNormalized, hr.normal, refractRatio);
        }

        newRay = Ray(hr.hitPoint, dir);
        return true;
    }

};

#endif