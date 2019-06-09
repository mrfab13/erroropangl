#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <freeglut.h>
#include <iostream>


class camera
{
public:
	camera();
	~camera();
	void initializeCamera();
	void calculate(GLfloat currentTime, int type);
	glm::mat4 getView();
	glm::mat4 getProj();
	glm::mat4 Model(glm::vec3 position, glm::vec3 scale, glm::mat4 rotationz);
	glm::mat4 MVP(glm::vec3 postion, glm::vec3 scale, glm::mat4 rotationZ);

	glm::mat4 SetProj(glm::mat4 project);

private:

	glm::vec3 camPos;
	glm::vec3 camLookDir;
	glm::vec3 camUpDir;

	glm::mat4 rotMat;
	glm::mat4 rotMat2;

	glm::vec4 newPos;
	
	glm::mat4 proj;

	glm::mat4 view;
	glm::vec3 camTar;

};

extern camera* currentCamera;
