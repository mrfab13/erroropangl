#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <fmod.hpp>
#include "ShaderLoader.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Audio.h"
#include "Input.h"
#include "PlayerManager.h"
#include "Camera.h"
#include "Manager.h"
#include "TextLabel.h"
#include "EnemyManager.h"
#include "TextureLoader.h"
#include "MeshManager.h"
#include "CubeMap.h"
#include "Model.h"
#include "ModelMesh.h"

using namespace std;

ShaderLoader m_shader;

GLuint program = NULL;
GLuint programMap = NULL;

GLuint VBO;
GLuint VAO;
GLuint EBO;
GLuint VBObg;
GLuint VAObg;
GLuint EBObg;
GLuint VBOe1;
GLuint VAOe1;
GLuint EBOe1;

GLfloat currentTime;
GLfloat pasttime = 0;
GLfloat deltaTime;

int fps = 0;

CubeMap cubemap;
LoadTexture TL;
Audio1 audio;
Input input;
camera camera1;
PlayerManager playermanager;
manager manager1;
EnemyManager enemymanager;
MeshManager meshmanager;
TextLabel label1; //score
TextLabel label2; //actual score
TextLabel label3; //menu
TextLabel label4; //sub menu
TextLabel label5; //deathscrenn
TextLabel label6; //win/loose
TextLabel label7; //level screen
TextLabel label8; //FPS

GLuint player;
GLuint e1;
GLuint bg;

Model model;

float TotalScore =  0.0f;
bool startplay = false;
bool restartplay = true;
int menuno = 0;
bool winner = false;
int gameRound = 1;
float rotO = 0.0f;

glm::vec3 rotationAxisZ = glm::vec3(1.0f, 0.0f, 0.0f);
float rotationAngle = 0;
glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);


GLfloat vertices[] //player
{	
	-0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	-0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
	0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,

	-0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

	0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

	0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	-0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

	-0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	-0.5f, 0.0f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

	0.0f, 0.5f, 0.0f,		0.0f, 1.0f, 1.0f,	0.5f, 0.0f,
};

GLuint indices[] =
{
	1, 4, 3,
	1, 3, 2,

	4, 12, 5,
	6, 12, 7,
	8, 12, 9,
	10, 12, 11,
};

GLfloat vertices2[] //bg
{	//pos                    //colour
	-1.0f,	-1.0f,	1.0f,    0.0f, 0.0f, 1.0f,		0.0f, 1.0f,//bot left
	1.0f,	-1.0f,	-1.0f,    1.0f, 0.0f, 0.0f,		1.0f, 0.0f,// top right
	-1.0f,	-1.0f,	-1.0f,    0.0f, 1.0f, 0.0f,		0.0f, 0.0f, //top left
	1.0f,	-1.0f,	1.0f,	 0.0f, 1.0f, 0.0f,		1.0f, 1.0f, //bot right
};

GLuint indices2[] =
{
	0,1,2,	//1 
	0,3,1,	//2
};

GLfloat vertices3[] //enemie
{	//pos                    //colour
	-0.5f,	-0.5f,	0.0f,    0.0f, 0.0f, 1.0f,		0.0f, 1.0f,//bot left
	0.5f,	0.5f,	0.0f,    1.0f, 0.0f, 0.0f,		1.0f, 0.0f,// top right
	-0.5f,	0.5f,	0.0f,    0.0f, 1.0f, 0.0f,		0.0f, 0.0f, //top left
	0.5f,	-0.5f,	0.0f,	 0.0f, 1.0f, 0.0f,		1.0f, 1.0f, //bot right
};

GLuint indices3[] =
{
	0,1,2,	//1 
	0,3,1,	//2
};

void Render()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	cubemap.Render();



	if (input.CheckKeyDown('m') == true)
	{
		if (startplay == true)
		{
			audio.playSound(2);
			enemymanager.initializespeedanddir();
			playermanager.initializeObjPos();
			enemymanager.initializeEPos();
			enemymanager.initializeE2Pos();
			gameRound = 3;
			startplay = false;
			restartplay = true;
			winner = false;
			menuno = 2;
		}
	}

	if (restartplay == true)
	{

		if (menuno == 0)
		{
			input.inputdelay(input);
			if (input.CheckKeyDown('o') == true && input.checkDownFirst(input, 'o') == true)
			{
				menuno = 1;
			}
			if (input.CheckKeyDown('p') == true)
			{
				gameRound = 1;
				enemymanager.initializespeedanddir();
				playermanager.initializeObjPos();
				enemymanager.initializeEPos();
				enemymanager.initializeE2Pos();
				TotalScore = 0.0f;
				startplay = true;
				restartplay = false;
			}
			if (input.CheckKeyDown('q') == true)
			{
				glutLeaveMainLoop();
			}
			label3.Render();
		}
		else if (menuno == 1)
		{
			label4.Render();
			input.inputdelay(input);
			if (input.CheckKeyDown('o') == true && input.checkDownFirst(input, 'o') == true)
			{
				menuno = 0;
			}
		}
		else if (menuno == 2)
		{
			//game over
			label5.Render();
			if (winner == false)
			{
				label6.SetText("loser");
			}
			else
			{
				label6.SetText("winner");
			}
			label2.SetPosition(glm::vec2(-135.0f, 190.0f));
			label6.Render();
			label2.Render();
			label2.SetPosition(glm::vec2(-400.0f, 300.0f));

			if (input.CheckKeyDown('o') == true)
			{
				menuno = 0;
			}

		}
		else if (menuno == 3)
		{
			//next round 
			label7.Render();
			label2.SetPosition(glm::vec2(-125.0f, 190.0f));
			label2.Render();
			label2.SetPosition(glm::vec2(-400.0f, 300.0f));
			if (input.CheckKeyDown('o') == true)
			{
				menuno = 0;
				startplay = true;
				restartplay = false;
			}
		}

	}

	if (startplay == true)
	{
		if (gameRound == 1)
		{
			camera1.calculate(currentTime);


			#pragma region "bg"

			/*glm::mat4 backProj_calc = camera1.MVP(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(2.0f, 1.0f, 2.0f), rotationZ);
			glm::mat4 backmodel = camera1.Model(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(2.0f, 1.0f, 2.0f), rotationZ);

			glUseProgram(program);

			GLuint mvpLoc2 = glGetUniformLocation(program, "proj_calc");
			glUniformMatrix4fv(mvpLoc2, 1, GL_FALSE, glm::value_ptr(backProj_calc));

			GLuint modelback = glGetUniformLocation(program, "model");
			glUniformMatrix4fv(modelback, 1, GL_FALSE, glm::value_ptr(backmodel));


			glBindVertexArray(VAObg);
			glBindTexture(GL_TEXTURE_2D, bg);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glUseProgram(0);
*/
			#pragma endregion 

			#pragma region "player"
			glUseProgram(program);

			playermanager.movement(deltaTime);


			glm::vec3 objPosition = glm::vec3(0.5f, 0.0f, 0.0f);
			objPosition += playermanager.GetObjectPos();
			glm::vec3 objscale = glm::vec3(0.25f, 0.25f, 0.25f);



			glm::mat4 mvp = camera1.MVP(objPosition, objscale, rotationZ);
			glm::mat4 playermodel = camera1.Model(objPosition, objscale, rotationZ);


			GLuint mvpLoc = glGetUniformLocation(program, "proj_calc");
			glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

			GLuint pmodel = glGetUniformLocation(program, "model");
			glUniformMatrix4fv(pmodel, 1, GL_FALSE, glm::value_ptr(playermodel));


			glBindVertexArray(VAO);

			glBindTexture(GL_TEXTURE_2D, player);

			glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glUseProgram(0);
#pragma endregion 

			#pragma region "e1"

			enemymanager.Emovement(deltaTime, manager1.GetSCREEN_W(), manager1.GetSCREEN_H(), audio, 1);

			glm::vec3 e1pos = glm::vec3(0.0f, 0.0f, 1.0f);
			e1pos += enemymanager.GetEPos();
			glm::vec3 e1scale = glm::vec3(1.0f, 1.0f, 1.0f);

			glm::mat4 Proj_calc = camera1.MVP(e1pos, e1scale, rotationZ);
			glm::mat4 enemyModel = camera1.Model(e1pos, e1scale, rotationZ);

			glUseProgram(program);

			GLuint mvpLoc3 = glGetUniformLocation(program, "proj_calc");
			glUniformMatrix4fv(mvpLoc3, 1, GL_FALSE, glm::value_ptr(Proj_calc));

			GLuint eModelLoc = glGetUniformLocation(program, "model");
			glUniformMatrix4fv(eModelLoc, 1, GL_FALSE, glm::value_ptr(enemyModel));

			glBindVertexArray(VAOe1);
			glBindTexture(GL_TEXTURE_2D, e1);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glUseProgram(0);

#pragma endregion 

			glm::vec4 playerbox(objPosition.y , objPosition.y - objscale.y, objPosition.x, objPosition.x + objscale.x); //up down left right
			glm::vec4 enemybox(e1pos.y, e1pos.y - e1scale.y, e1pos.x, e1pos.x + e1scale.x);
			bool collision = false;
			//collision = enemymanager.checkCollision(playerbox, enemybox);

			if (collision == true)
			{
				audio.playSound(2);
				enemymanager.initializespeedanddir();
				playermanager.initializeObjPos();
				enemymanager.initializeEPos();
				enemymanager.initializeE2Pos();
				gameRound = 3;
				startplay = false;
				restartplay = true;
				menuno = 3;
			}

			TotalScore = TotalScore + deltaTime;
			int displayScore = static_cast<int>(TotalScore);
			label2.SetText(to_string(displayScore));
			label1.Render();
			label2.Render();
		}


	}


	label8.SetText(to_string(fps));
	label8.Render();

	playermanager.FIRETHECANNONS_AHHHHHHHHH(deltaTime, &camera1, program);


	glBindVertexArray(0);
	glUseProgram(0);



	glm::vec3 modelpos = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 modelscale = glm::vec3(0.2f, 0.2f, 0.2f);
	model.Render(modelpos, modelscale, rotationZ);



	glutSwapBuffers();
}

void Update()
{
	audio.update();
	
	currentCamera = &camera1;
	cubemap.Update();
	currentTime = (GLfloat)glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - pasttime)* 0.1f;
	pasttime = currentTime;

	fps = manager1.FPS(deltaTime);

	glutPostRedisplay();

}

int main(int argc, char **argv) 
{
	manager1.SetScreenDimentions(1, 1280);
	manager1.SetScreenDimentions(2, 720);
	srand(static_cast <unsigned> (time(0)));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);


	glutInitWindowSize(static_cast<int>(manager1.GetSCREEN_W()), static_cast<int>(manager1.GetSCREEN_H()));
	glutCreateWindow("(0) : error C5145: must write to gl_Position");
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		cout << "somthin wrong cheif" << endl;
		system("pause");
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	camera1.SetProj(glm::perspective(45.0f, (float)manager1.GetSCREEN_W() / (float)manager1.GetSCREEN_H(), 0.1f, 10000.0f));


	glClearColor(1.0f, 0.3f, 0.3f, 1.0f);

	program = ShaderLoader::CreateProgram("backG.vs", "BlingPhongShader.fs");
	programMap = ShaderLoader::CreateProgram("CubeMap.vs", "CubeMap.fs");


	cubemap.setProgram(programMap);



	#pragma region "text"

	label1 = TextLabel(manager1, "score:", "ass/fonts/comic.ttf", glm::vec2(-600.0f, 300.0f));
	label2 = TextLabel(manager1, "", "ass/fonts/comic.ttf", glm::vec2(-400.0f, 300.0f));
	label3 = TextLabel(manager1, R"(dead memes: the game 
press p to play 
press q to quit 
press o for other)", "ass/fonts/comic.ttf", glm::vec2(-600.0f, 300.0f));
	label4 = TextLabel(manager1, R"(use WASD to move
press m ingame to instantly die
stay alive aslong as possible for the highest score
1500+ score is a win
game created by vaughan webb 
song used: MINE DIAMONDS - MineCraft Awesome Parodys 
press o to return to main menu )", "ass/fonts/comic.ttf", glm::vec2(-600.0f, 300.0f) /*glm::vec3(1.0f,1.0f,1.0f), 0.75f*/);
		
	label5 = TextLabel(manager1, R"(Game over man, GAME OVER
you are a 
with a final score of
1500+ to win
press o to return to menu)", "ass/fonts/comic.ttf", glm::vec2(-600.0f, 300.0f));

	label6 = TextLabel(manager1, "", "ass/fonts/comic.ttf", glm::vec2(-380.0f, 245.0f));
	label7 = TextLabel(manager1, R"(you died
try to do better in the next level
your current score is 
1500 score to win
press o to start the next level)", "ass/fonts/comic.ttf", glm::vec2(-600.0f, 300.0f));
	label8 = TextLabel(manager1, "0", "ass/fonts/comic.ttf", glm::vec2(550.0f, 300.0f)/*glm::vec3(1.0f, 1.0f, 1.0f), 0.5f*/);

#pragma endregion 


	cubemap.Create("yaris");


	#pragma region "player"

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (8 * (sizeof(GLfloat))), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (8 * (sizeof(GLfloat))), (GLvoid*)(3 * (sizeof(GLfloat))));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (8 * (sizeof(GLfloat))), (GLvoid*)(6 * (sizeof(GLfloat))));
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	player = TL.loadTexture("ass/pics/doge.jpg");
	glBindTexture(GL_TEXTURE_2D, player);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);


#pragma endregion 

	#pragma region "bg"

	//glGenVertexArrays(1, &VAObg);
	//glBindVertexArray(VAObg);

	//glGenBuffers(1, &EBObg);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBObg);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	//glGenBuffers(1, &VBObg);
	//glBindBuffer(GL_ARRAY_BUFFER, VBObg);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(2);

	//glActiveTexture(GL_TEXTURE2);
	//bg = TL.loadTexture("ass/pics/bruh.jpg");
	//glBindTexture(GL_TEXTURE_2D, bg);
	//glUniform1i(glGetUniformLocation(program, "tex"), 2);

#pragma endregion 

	#pragma region "enemie1"

	glGenVertexArrays(1, &VAOe1);
	glBindVertexArray(VAOe1);

	glGenBuffers(1, &EBOe1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOe1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);

	glGenBuffers(1, &VBOe1);
	glBindBuffer(GL_ARRAY_BUFFER, VBOe1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE3);
	e1 = TL.loadTexture("ass/pics/bazinga.jpg");
	glBindTexture(GL_TEXTURE_2D, e1);
	glUniform1i(glGetUniformLocation(program, "tex"), 3);

#pragma endregion 



	camera1.initializeCamera();
	audio.AudioInit();
	audio.Create("ass/sounds/takeonme2.mp3", 1);
	audio.Create("ass/Sounds/oof.wav", 2);
	audio.Create("ass/Sounds/bruh1.wav", 3);
	//audio.playSound(1);

	model = Model::Model("ass/models/pug/dog 1.obj", &camera1);

	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	glutKeyboardFunc(Input::KeyboardDown);
	glutKeyboardUpFunc(Input::KeyboardUp);

	glutSpecialFunc(Input::specialCharDown);
	glutSpecialUpFunc(Input::specialCharUp);

	glutMainLoop();

	return 0;
}
