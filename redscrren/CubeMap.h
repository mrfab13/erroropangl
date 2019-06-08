#pragma once
#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <SOIL.h>

#include <vector>
#include <windows.h>
#include <cstdlib>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Camera.h"

class CubeMap
{
	public:
		CubeMap();
		~CubeMap();
		void Create(std::string selection);
		void Update();
		void Render();
		glm::mat4 MapMVP();
		GLuint setProgram(GLuint programMap);
		GLuint returnVBO();
		GLuint returnVAO();
		GLuint returnEBO();
	
	private:
		glm::mat4 MVP;
		GLuint programMap;
		std::vector<std::string> texturex6;
		unsigned int textureID;

		GLuint VBOmap;
		GLuint VAOmap;
		GLuint EBOmap;

		GLfloat CubeMapVertices[24] = {};
		GLuint CubeMapIndices[36] = {};
};