/*
    Entry Point Of The Program
*/
#include "Image.hpp"
#include <iostream>
#include <glm/gtx/string_cast.hpp>


void printVec3(glm::vec3 const vec)
{
	std::cout << glm::to_string(vec) << std::endl;
}


int main()
{
	// change camera position -- move camera
	glm::vec3 cameraP(0.0f, 0.0f, 0.0f);
	// image 2
	//glm::vec3 cameraP(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraH(4.0f, 0.0f, 0.0f);
	glm::vec3 cameraV(0.0f, 4.0f, 0.0f);
	// camera field of view in degree
	// image 3
	float cameraVD = 20.0f;
	// smaller field of view
	//float cameraVD = 10.0f;
	// change lookAt -- rotate camera
	// image 4
	glm::vec3 lookAt(0.0f, 0.0f, -3.0f);
	// image 5
	//glm::vec3 lookAt(0.0f, 1.0f, -3.0f);
	// image 6
	//glm::vec3 lookAt(0.0f, -1.2f, -3.0f);
	// image 7
	//glm::vec3 lookAt(-1.0f, 0.0f, -3.0f);

	glm::vec3 vUp(0.0f, 1.0f, 0.0f);
	float wHratio = 1.0f;
	float aperture = 0.04f;
	// image 8
	//float aperture = 1.0f; //change aperture
	float focusDist = glm::length(cameraP - lookAt);
	Camera c(cameraP, cameraH, cameraV, cameraVD, lookAt, vUp, wHratio, aperture, focusDist);


	int imageH = 200;
	int imageW = 200;
	Image i(imageW, imageH, c);

	// The sequence of parameter: color, center, radius
	// image 9
	i.addLambertianObjectToScene(glm::vec3(0.9f, 0.9f, 0.8f), glm::vec3(0.0f, 0.5f, -5.0f), 1.0f);
	// image 10
	i.addMetalObjectToScene(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.0f, -5.0f, -7.0f), 5.0f);
	// image 11
	i.addDielectricObjectToScene( 10.0f, glm::vec3(-2.0f, 0.5f, -6.0f), 1.0f);
	
	i.printImage();


}