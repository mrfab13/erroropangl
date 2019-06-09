#include "Manager.h"

EnemyManager EnemyCollision;

GLfloat manager::GetSCREEN_H()
{
	return (SCREEN_H);
}

GLfloat manager::GetSCREEN_W()
{
	return (SCREEN_W);
}

void manager::SetScreenDimentions(int axis, int size)
{
	if (axis == 1)
	{
		SCREEN_W = static_cast<GLfloat>(size);
	}
	else if (axis == 2)
	{
		SCREEN_H = static_cast<GLfloat>(size);
	}
}

int manager::FPS(GLfloat deltatime)
{
	if (deltatime > 0.0f)
	{
		secondtimer += deltatime;
	}

	framecount++;

	if (secondtimer > 100.0f)
	{
		fps = framecount;
		framecount = 0;
		secondtimer = 0;
	}
	return (fps);
}

bool manager::getplayerCollision()
{
	return (playerCollision);
}

void manager::setplayerCollision(bool playercollision)
{
	playerCollision = playercollision;
}

int manager::EnemysBegin(GLfloat deltatime, camera* camera1, Model* model, int Wavecheck, bool resetPOS, PlayerManager* playermanager)
{
	if (enemies.size() == 0 || resetPOS == true)
	{

		if (resetPOS == true)
		{
			enemies.erase(enemies.begin(), enemies.end());
			enemies.clear();
		}
		else
		{
			Wavecheck += Wavecheck * 0.5;

		}
		for (int i = 0; i < Wavecheck; i++)
		{
			glm::vec3 modelpos;
			glm::vec3 modelscale = glm::vec3(0.2f, 0.2f, 0.2f);

			int pos = rand() % 4;
			if (pos == 0)
			{
				 modelpos = glm::vec3(3.8f, -1.0f, -6.0f);
			}
			else if (pos == 1)
			{
				 modelpos = glm::vec3(-3.8f, -1.0f, -6.0f);
			}
			else if (pos == 2)
			{
				 modelpos = glm::vec3(-3.8f, -1.0f, 0.0f);
			}
			else
			{
				 modelpos = glm::vec3(3.8f, -1.0f, 0.0f);
			}

			enemies.push_back(new EnemyManager(modelpos, modelscale));
			enemies.back()->initializespeedanddir();

			
		}
	}

	EnemiesProcess(deltatime, camera1, model, playermanager, Wavecheck);

	return(Wavecheck);
}

void manager::EnemiesProcess(GLfloat deltatime, camera* camera1, Model* model, PlayerManager* playermanager, int Wavecheck)
{
	glm::vec3 rotationAxisZ = glm::vec3(1.0f, 0.0f, 0.0f);
	float rotationAngle = 0;
	glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);

	for (int i = 0; i < (int)enemies.size(); i++)
	{

		enemies.at(i)->Emovement(deltatime, 1, Wavecheck);
		model->Render(enemies.at(i)->GetModelpos(), enemies.at(i)->GetModelscale(), rotationZ);


		if (enemies.size() > i)
		{
			for (int j = 0; j < (int)(playermanager->ReturnBullets().size()); j++)
			{
				if (enemies.size() == i)
				{
					break;
				}
				std::vector<Object*> temp = playermanager->ReturnBullets();
				float Boarder1 = -0.2f;
				float Boarder2 = -0.2f;

				glm::vec4 box1 = glm::vec4(temp.at(j)->retunrPpos().z, temp.at(j)->retunrPpos().z + Boarder1, temp.at(j)->retunrPpos().x, temp.at(j)->retunrPpos().x - Boarder1); //up down left right
				glm::vec4 box2 = glm::vec4(enemies.at(i)->GetModelpos().z, enemies.at(i)->GetModelpos().z + Boarder2, enemies.at(i)->GetModelpos().x, enemies.at(i)->GetModelpos().x - Boarder2);
				bool temp2 = EnemyCollision.checkCollision(box1, box2);
				if (temp2 == true)
				{
					std::vector<EnemyManager*> temp;

					for (int k = 0; k < (int)enemies.size(); k++)
					{
						if (i != k)
						{
							temp.push_back(enemies.at(k));
						}
					}
					delete enemies[i];
					enemies.erase(enemies.begin(), enemies.end());
					enemies.clear();

					for (int k = 0; k < (int)temp.size(); k++)
					{
						enemies.push_back(temp.at(k));
					}
					temp.erase(temp.begin(), temp.end());
					temp.clear();
				}
			}

			if (enemies.size() == i)
			{
				break;
			}

			float Boarder1 = -0.2f;
			float Boarder2 = -0.2f;
			float playeroffsetx = 0.4f;
			float playeroffsetz = 0.1f;

			glm::vec4 box1 = glm::vec4(playermanager->GetObjectPos().z + 0.2f, playermanager->GetObjectPos().z + Boarder1 + playeroffsetz, playermanager->GetObjectPos().x + playeroffsetx, playermanager->GetObjectPos().x - Boarder1 + playeroffsetx); //up down left right
			glm::vec4 box2 = glm::vec4(enemies.at(i)->GetModelpos().z, enemies.at(i)->GetModelpos().z + Boarder2, enemies.at(i)->GetModelpos().x, enemies.at(i)->GetModelpos().x - Boarder2);
			bool temp3 = EnemyCollision.checkCollision(box1, box2);
			if (temp3 == true)
			{
				playerCollision = true;
				break;
			}


		}




	}
}

