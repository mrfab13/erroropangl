#pragma once
#include "Camera.h"
#include "TextureLoader.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <freeglut.h>
#include <SOIL.h>





class Object
{
public:
	Object(int bulletDir, float DeltaTime, glm::vec3 objPos, GLuint program);
	~Object();
	bool Process(float DeltaTime, camera* camera1, GLuint program);
	void Render(camera* camera1, GLuint program);

private:
	float lifetime = 0.0f;
	float position = 0.0f;
	glm::vec3 Ppos = glm::vec3(0.0f, 0.0f, 0.0f); 
	glm::vec3 veloc = glm::vec3(0.0f, 0.0f, 0.0f);

	unsigned int textureID;
	GLuint texture;
	GLuint VBOmap;
	GLuint VAOmap;
	GLuint EBOmap;

	GLfloat vertices4[32] { };

	GLuint indices4[6] = { };
};