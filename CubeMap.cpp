#include "CubeMap.h"

CubeMap::CubeMap()
{

}

CubeMap::~CubeMap()
{
}

void CubeMap::Create(std::string selection)
{
	//vertcies
	for (int i = 0; i < 8; i++)
	{
		if (i < 4)
		{
			CubeMapVertices[i * 3] = -1.0f;
			for (int j = 0; j < 4; j++)
			{
				if (j < 2)
				{
					CubeMapVertices[(j * 3) + 1] = 1.0f;
				}
				else
				{
					CubeMapVertices[(j * 3) + 1] = -1.0f;
				}

				if (j % 2 == 0)
				{
					CubeMapVertices[(j * 3) + 2] = 1.0f;
				}
				else
				{
					CubeMapVertices[(j * 3) + 2] = -1.0f;
				}
			}
		}
		else
		{
			CubeMapVertices[i * 3] = 1.0f;
			for (int j = 4; j < 8; j++)
			{
				if (j < 6)
				{
					CubeMapVertices[(j * 3) + 1] = 1.0f;
				}
				else
				{
					CubeMapVertices[(j * 3) + 1] = -1.0f;
				}

				if (j % 2 == 0)
				{
					CubeMapVertices[(j * 3) + 2] = 1.0f;
				}
				else
				{
					CubeMapVertices[(j * 3) + 2] = -1.0f;
				}
			}
		}
	}

	GLuint temp[] = {
		3,2,6,
		3,6,7,

		1,4,0,
		1,5,4,

		2,1,0,
		2,3,1,

		3,5,1,
		3,7,5,

		6,4,5,
		6,5,7,

		4,2,0,
		4,6,2,

	};

	for (int i = 0; i < (int)sizeof(temp)/ sizeof(temp[0]); i++)
	{
		CubeMapIndices[i] = temp[i];
	}

	GLuint VAOtemp = NULL;

	glGenVertexArrays(1, &VAOtemp);
	glBindVertexArray(VAOtemp);

	glGenBuffers(1, &VBOmap);
	glBindBuffer(GL_ARRAY_BUFFER, VBOmap);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeMapVertices), CubeMapVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBOmap);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOmap);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeMapIndices), CubeMapIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	VAOmap = VAOtemp;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	texturex6.push_back("right.png");	//right
	texturex6.push_back("left.png");	//left
	texturex6.push_back("top.png");		//top
	texturex6.push_back("bottom.png");	//botom
	texturex6.push_back("back.png");	//back
	texturex6.push_back("front.png");	//front



	int width, height;
	unsigned char* image;

	for (GLuint i = 0; i < 6; i++)
	{
		std::string fullPathName = "ass/CubeMap/";
		fullPathName.append(selection);
		fullPathName.append("/");
		fullPathName.append(texturex6[i]);
		image = SOIL_load_image(fullPathName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);


		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		SOIL_free_image_data(image);

	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMap::Update()
{
	MVP = currentCamera->getProj() * currentCamera->getView() * glm::scale(glm::mat4(), glm::vec3(2000.0f, 2000.0f, 2000.0f));  
}

void CubeMap::Render()
{
	glUseProgram(programMap);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glUniform1i(glGetUniformLocation(programMap, "cubeSampler"), 0);
	glUniformMatrix4fv(glGetUniformLocation(programMap, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

	glBindVertexArray(VAOmap);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

glm::mat4 CubeMap::MapMVP()
{
	return (MVP);
}

GLuint CubeMap::setProgram(GLuint programMap)
{
	this->programMap = programMap;
	return (programMap);
}

GLuint CubeMap::returnVBO()
{
	return (VBOmap);
}

GLuint CubeMap::returnVAO()
{
	return (VAOmap);
}

GLuint CubeMap::returnEBO()
{
	return (EBOmap);
}
