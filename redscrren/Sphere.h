#pragma once


#include <glew.h>
#include <freeglut.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

class Sphere
{
public:

	Sphere();
	~Sphere();

	void Render();

private:
	GLuint VAOsp;

	GLuint IndiceCount;
	int DrawType;
};

