#pragma once

#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Audio.h"
#include "Input.h"
#include "Object.h"


class PlayerManager
{
public:

	PlayerManager();
	~PlayerManager();
	glm::vec3 GetObjectPos();
	void SetObjectPos(glm::vec3);
	void initializeObjPos();
	void movement(GLfloat deltaTime);
	void setbulletDir(int Dir);
	void FIRETHECANNONS_AHHHHHHHHH(GLfloat deltatime, camera* camera1, GLuint program);
	void BulletProcess(GLfloat deltaTime, camera* camera1, GLuint program);

private:
	glm::vec3 objPos;
	int bulletDir;
	GLfloat reloadTime = 0.0f;
	std::vector<Object*> bullets;
};