#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <glm.hpp>
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <string>
#include <iostream>
#include "ShaderLoader.h"
#include "Manager.h"


struct FontChar
{
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};

class TextLabel
{
public:
	TextLabel();
	TextLabel(manager& manager1, std::string text, std::string font, glm::vec2 pos, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float scale = 1.0f);
	~TextLabel();
	void Render();
	void SetText(std::string newText) { text = newText; };
	void SetColor(glm::vec3 newColor) { color = newColor; };
	void SetScale(GLfloat newScale) { scale = newScale; };
	void SetPosition(glm::vec2 newPosition) { position = newPosition; };


private:

	GLuint GeneratTexture(FT_Face face);
	std::string text;
	GLfloat scale;
	glm::vec3 color;
	glm::vec2 position;

	GLuint VAO, VBO, program;
	glm::mat4 proj;
	std::map<GLchar, FontChar> Characters;

};

