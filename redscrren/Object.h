#pragma once
#include <glew.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <SOIL.h>

#include "Camera.h"




class Object
{
public:
	void LoadTexture(const char * path);
	Object(int bulletDir, float DeltaTime, glm::vec3 objPos, GLuint program);
	~Object();
	bool Process(float DeltaTime, camera* camera1, GLuint program);
	void Render(camera* camera1, GLuint program);
	glm::vec3 retunrPpos();

private:
	unsigned char* image;
	float lifetime = 0.0f;
	float position = 0.0f;
	glm::vec3 Ppos = glm::vec3(1.0f, 1.0f, 1.0f); 
	glm::vec3 veloc = glm::vec3(0.0f, 0.0f, 0.0f);

	GLuint texture;
	GLuint VBOmap;
	GLuint VAOmap;
	GLuint EBOmap;

	GLfloat vertices4[32] { };

	GLuint indices4[6] = { };
};