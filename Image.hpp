#ifndef IMAGE_HPP
#define IMAGE_HPP
#define SAMPLE_TIME 100

#include "Camera.hpp"
#include "Sphere.hpp"
#include <iostream>
#include <fstream>
#include <vector>

class Image{
    private:
        int imageWidth;
        int imageHeight;
        Camera camera;

    public:
        std::vector<Sphere *> sphereList;

    public:
        Image(int w, int h, Camera c){
            imageWidth = w;
            imageHeight = h;
            camera = c;
        }

        bool hitAny(std::vector<Sphere*> hArray, int hSize, Ray & r, float tMin, float tMax, HitRecord & rec)
        {
            bool isHitAny = false;
            HitRecord tempRecord;
            for(int i = 0; i < hSize; i++)
            {
                if(hArray[i]->hit(r, tMin, tMax, tempRecord))
                {
                    isHitAny = true;
                    tMax = tempRecord.t;
                    rec = tempRecord;
                }
            }
            return isHitAny;
        }

        glm::vec3 printSky(Ray & r)
        {
            glm::vec3 normalDir = glm::normalize(r.getDirection());
            float t = 0.5f * (normalDir.y + 1.0f);
            return (1.0f-t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
        }

        glm::vec3 rayColor(Ray & r, std::vector<Sphere*> hArray, int hArraySize, HitRecord & record, int depth)
        {
            glm::vec3 color;

            float tMIN = 0.001f;
            float tMAX = 100.0f;
            if(depth <= 0)
            {
                return glm::vec3(0, 0, 0);
            }

            if(hitAny(hArray, hArraySize, r, tMIN, tMAX, record))
            {
                Ray childRay;
                glm::vec3 changed;
                if(record.matP -> sendNewRay(r, record, changed, childRay))
                {
                    color = changed * rayColor(childRay, hArray, hArraySize, record, depth - 1);
                }else
                {
                    color = glm::vec3(0.0f, 0.0f, 0.0f);
                }
            }else{
                color = printSky(r);
            }

            return color;
        }
        
        void castColor(glm::vec3 const color)
        {
            int x = color.x * 255.99;
            int y = color.y * 255.99;
            int z = color.z * 255.99;
            std::cout << x << " " << y << " " << z << "\n";
        }

        void addLambertianObjectToScene(glm::vec3 color, glm::vec3 center, float radius)
        {
            Material *m = new Lambertian(color);
            Sphere *s = new Sphere(center, radius, m);
            sphereList.push_back(s);
        }

        void addMetalObjectToScene(glm::vec3 color, glm::vec3 center, float radius)
        {
            Material *m = new Metal(color);
            Sphere *s = new Sphere(center, radius, m);
            sphereList.push_back(s);
        }

        void addDielectricObjectToScene(float ir, glm::vec3 center, float radius)
        {
            Material *m = new Dielectrics(ir);
            Sphere *s = new Sphere(center, radius, m);
            sphereList.push_back(s);
        }

        void printImage()
        {
            std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
            int depth = 10;
            for(int j = imageHeight - 1; j >= 0; j--)
            {
                for(int i = 0; i < imageWidth; i++)
                {
                    HitRecord record;
                    glm::vec3 color(0.0f, 0.0f, 0.0f);
                    for(int k = 0; k < SAMPLE_TIME; k++)
                    {
                        float u = (float(i) + drand48())/ (imageWidth - 1);
                        float v = (float(j) + drand48())/ (imageHeight - 1); 
                        Ray ray = camera.getRay(u, v);
                        color += rayColor(ray, sphereList, sphereList.size(), record, depth);
                    }
                    color.x /= SAMPLE_TIME;
                    color.y /= SAMPLE_TIME;
                    color.z /= SAMPLE_TIME;
                    castColor(color);
                }
            }
        }

};

#endif