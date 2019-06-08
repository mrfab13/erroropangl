#include "Object.h"

LoadTexture TL;

Object::Object(int bulletDir, float DeltaTime, glm::vec3 objPos, GLuint program)
{

	if (bulletDir <= 3)
	{
		veloc.y -= 1.0f * DeltaTime;
	}
	else if (bulletDir >= 7)
	{
		veloc.y += 1.0f * DeltaTime;
	}

	if (bulletDir % 3 == 0) // 963
	{
		veloc.x += 1.0f * DeltaTime;
	}
	else if (bulletDir % 3 == 1) //741
	{
		veloc.x -= 1.0f * DeltaTime;
	}

	Ppos = objPos;

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

	glGenVertexArrays(1, &VAOtemp);
	glBindVertexArray(VAOtemp);

	glGenVertexArrays(1, &VAOmap);
	glBindVertexArray(VAOmap);

	glGenBuffers(1, &EBOmap);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOmap);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices4), indices4, GL_STATIC_DRAW);

	glGenBuffers(1, &VBOmap);
	glBindBuffer(GL_ARRAY_BUFFER, VBOmap);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	VAOmap = VAOtemp;

	glActiveTexture(GL_TEXTURE3);
	texture = TL.loadTexture("ass/pics/bazinga.jpg");
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "tex"), 3);


}

Object::~Object()
{

}

bool Object::Process(float DeltaTime, camera* camera1, GLuint program)
{
	Ppos += veloc;
	lifetime += DeltaTime;
	Render(camera1, program);
	if (lifetime >= 15.0f)
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

	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::mat4 Proj_calc = camera1->MVP(Ppos, scale, rotationZ);
	glm::mat4 enemyModel = camera1->Model(Ppos, scale, rotationZ);




	glUseProgram(program);

	GLuint mvpLoc3 = glGetUniformLocation(program, "proj_calc");
	glUniformMatrix4fv(mvpLoc3, 1, GL_FALSE, glm::value_ptr(Proj_calc));

	GLuint eModelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(eModelLoc, 1, GL_FALSE, glm::value_ptr(enemyModel));

	glBindVertexArray(VAOmap);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);

}
