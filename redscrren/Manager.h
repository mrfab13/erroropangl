#pragma once
//#include <freeglut.h>
#include <glm.hpp>
#include "gtc/type_ptr.hpp"
#include "ShaderLoader.h"
#include "EnemyManager.h"

#include "Model.h"
#include "ModelMesh.h"
#include "PlayerManager.h"



class manager
{
public:
	GLfloat GetSCREEN_H();
	GLfloat GetSCREEN_W();
	void SetScreenDimentions(int axis, int size);
	int FPS(GLfloat deltatime);
	bool getplayerCollision();
	void setplayerCollision(bool playercollision);
	int EnemysBegin(GLfloat deltatime, camera* camera1, Model* model, int Wavecheck, bool resetPOS, PlayerManager* playermanager);
	void EnemiesProcess(GLfloat deltatime, camera* camera1, Model* model, PlayerManager* playermanager, int Wavecheck);

private:

	GLfloat SCREEN_H;
	GLfloat SCREEN_W;
	GLfloat secondtimer;
	int framecount = 0;
	int fps = 0;
	bool playerCollision = false;
	std::vector<EnemyManager*> enemies;


};