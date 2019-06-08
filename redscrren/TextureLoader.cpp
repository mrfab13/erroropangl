//local includes
#include "TextureLoader.h"
#include "ShaderLoader.h"

//library Includes
#include <iostream>
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include "glm.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtc\type_ptr.hpp"


//stores what number the value is for the texture

//path is where the image is stored
GLuint LoadTexture::loadTexture(const char *path) {

	GLuint texture;

	unsigned char* image;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//making the texture smooth
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);


	int width, height;
	//path is the path to the directory with the texture to load
	image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//return the texture
	return texture;

}


