#include "Object.h"

void Object::LoadTexture(const char *path)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//making the texture smooth
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);


	int width, height;
	//path is the path to the directory with the texture to load
	this->image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->image);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(this->image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Object::Object(int bulletDir, float DeltaTime, glm::vec3 objPos, GLuint program)
{
	bool render = false;
	float speed = 0.07f;
	if (bulletDir <= 3)
	{
		veloc.z += 1.0f * speed;
		render = true;
	}
	else if (bulletDir >= 7)
	{
		veloc.z -= 1.0f * speed;
		render = true;

	}

	if (bulletDir % 3 == 0) // 963
	{
		veloc.x += 1.0f * speed;
		render = true;

	}
	else if (bulletDir % 3 == 1) //741
	{
		veloc.x -= 1.0f * speed;
		render = true;
	}

	glm::vec3 offset(0.5f, 0.15f, 0.0f);
	Ppos = objPos + offset;

	if (render == true)
	{
		GLfloat vertices4[]
		{	//pos                    //colour
			-1.0f,	-1.0f,	1.0f,    0.0f, 0.0f, 1.0f,		0.0f, 1.0f,//bot left
			1.0f,	-1.0f,	-1.0f,    1.0f, 0.0f, 0.0f,		1.0f, 0.0f,// top right
			-1.0f,	-1.0f,	-1.0f,    0.0f, 1.0f, 0.0f,		0.0f, 0.0f, //top left
			1.0f,	-1.0f,	1.0f,	 0.0f, 1.0f, 0.0f,		1.0f, 1.0f, //bot right
		};

		GLuint indices4[] =
		{
			0,1,2,	//1 
			0,3,1,	//2
		};


		GLuint VAOtemp = NULL;

		glGenVertexArrays(1, &this->VAOmap);
		glBindVertexArray(this->VAOmap);

		glGenBuffers(1, &this->EBOmap);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBOmap);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices4), indices4, GL_STATIC_DRAW);

		glGenBuffers(1, &this->VBOmap);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBOmap);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glActiveTexture(GL_TEXTURE0);
		LoadTexture("ass/pics/bazinga.jpg");
		glBindTexture(GL_TEXTURE_2D, this->texture);
		glUniform1i(glGetUniformLocation(program, "tex"), 0);
		std::cout << "pew" << std::endl;
	}
}

Object::~Object()
{
	
}

bool Object::Process(float DeltaTime, camera* camera1, GLuint program)
{
	Ppos += veloc * DeltaTime;
	lifetime += DeltaTime;
	Render(camera1, program);
	if (lifetime >= 50.0f)
	{
		return (false);
	}
	return(true);
}

void Object::Render(camera* camera1, GLuint program)
{
	glm::vec3 rotationAxisZ = glm::vec3(1.0f, 0.0f, 0.0f);
	float rotationAngle = 0;
	glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);

	glm::vec3 scale = glm::vec3(0.05f, 0.05f, 0.05f);
	glm::mat4 Proj_calc = camera1->MVP(this->Ppos, scale, rotationZ);
	glm::mat4 enemyModel = camera1->Model(this->Ppos, scale, rotationZ);

	glUseProgram(program);

	GLuint mvpLoc3 = glGetUniformLocation(program, "proj_calc");
	glUniformMatrix4fv(mvpLoc3, 1, GL_FALSE, glm::value_ptr(Proj_calc));

	GLuint eModelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(eModelLoc, 1, GL_FALSE, glm::value_ptr(enemyModel));

	glBindVertexArray(this->VAOmap);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);

}

glm::vec3 Object::retunrPpos()
{
	return (Ppos);
}
