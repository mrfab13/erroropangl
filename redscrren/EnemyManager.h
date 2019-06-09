#pragma once

#include <freeglut.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Audio.h"

class EnemyManager
{
public:

	EnemyManager();
	EnemyManager(glm::vec3 modelpos, glm::vec3 modelscale);
	~EnemyManager();
	glm::vec3 GetEPos();
	glm::vec3 GetE2Pos();
	void SetEPos(glm::vec3);
	void SetE2Pos(glm::vec3);

	glm::vec3 GetModelpos();
	glm::vec3 GetModelscale();

	void initializeEPos();
	void initializeE2Pos();

	glm::vec2 Getrandxy();
	void Setrandxy(glm::vec2);



	void initializespeedanddir();
	void Emovement(GLfloat deltaTime, int type, int Wavecheck);

	bool checkCollision(glm::vec4 box1, glm::vec4 box2);


private:
	glm::vec3 ePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 e2Pos = glm::vec3(3.0f, 0.0f, 0.0f);


	int dir = 1;
	int dir2 = 1;
	glm::vec2 randxy = glm::vec2(0.0f, 0.0f);

	float speed = 2.0f;

	glm::vec3 Modelpos;
	glm::vec3 Modelscale;
};