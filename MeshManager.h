#pragma once

#include <freeglut.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Audio.h"
#include "Input.h"


class MeshManager
{
public:

	MeshManager();
	~MeshManager();
	GLfloat returnvert(int type);
	GLint returnindec(int type);


	
private:
	glm::vec3 objPos;
};