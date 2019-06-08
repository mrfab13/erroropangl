#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

glm::vec3 EnemyManager::GetEPos()
{
	return (ePos);
}

glm::vec3 EnemyManager::GetE2Pos()
{
	return (e2Pos);
}

void EnemyManager::SetEPos(glm::vec3 temp)
{
	ePos = temp;
}

void EnemyManager::SetE2Pos(glm::vec3 temp)
{
	e2Pos = temp;

}

void EnemyManager::initializeEPos()
{
	ePos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void EnemyManager::initializeE2Pos()
{
	e2Pos = glm::vec3(0.0f, 0.0f, 0.0f);

}

glm::vec2 EnemyManager::Getrandxy()
{
	return (randxy);
}

void EnemyManager::Setrandxy(glm::vec2)
{
	randxy.x = (0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f - 0.5f))));
	randxy.y = (0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f - 0.5f))));

}

void EnemyManager::initializespeedanddir()
{
	speed = 0.001f;
	dir = 1;
	dir2 = 1;
	Setrandxy(randxy);

}

void EnemyManager::Emovement(GLfloat deltaTime, float ScreenW, float screenH, Audio1& audio2, int type)
{

	speed += 0.00001f * deltaTime;
	glm::vec3 temp;
	glm::vec3 temp2;
	temp = GetEPos();
	temp2 = GetE2Pos();

	 //wd
	if (type == 1 && (dir == 1))
	{
		temp.y += speed * deltaTime;
		temp.x += speed * deltaTime;
		SetEPos(temp);
		if (temp.y > 1.0f)
		{
			dir = 4;
			audio2.playSound(3);

		}
		if (temp.x > 1.0f)
		{
			dir = 2;
			audio2.playSound(3);
		}
	}



 //aw
		if (type == 1 && dir == 2)
		{
			temp.x -= speed * deltaTime;
			temp.y += speed * deltaTime;
			SetEPos(temp);
			if (temp.x < (-1.0f))
			{
				dir = 1;
				audio2.playSound(3);

			}
			if (temp.y >(1.0f))
			{
				dir = 3;
				audio2.playSound(3);

			}
		}


	
  //sa
	
		if (type == 1 && dir == 3)
		{
			temp.y -= speed * deltaTime;
			temp.x -= speed * deltaTime;
			SetEPos(temp);
			if (temp.y < (-1.0f))
			{
				dir = 2;
				audio2.playSound(3);
			}
			if (temp.x < (-1.0f))
			{
				dir = 4;
				audio2.playSound(3);
			}
		}


	
  //ds
	
		if (type == 1 && dir == 4)
		{
			temp.x += speed * deltaTime;
			temp.y -= speed * deltaTime;
			SetEPos(temp);
			if (temp.x > (1.0f))
			{
				dir = 3;
				audio2.playSound(3);
			}
			if (temp.y < (-1.0f))
			{
				dir = 1;
				audio2.playSound(3);
			}
		}

}

bool EnemyManager::checkCollision(glm::vec4 box1, glm::vec4 box2)
{
	bool collision = false;
	if ((box1.x > box2.x) && (box1.y < box2.x))
	{
		if ((box1.z < box2.z) && (box1.w > box2.z))
		{
			collision = true;
		}
		if ((box1.z < box2.w) && (box1.w > box2.w))
		{
			collision = true;
		}
	}
	if ((box1.x > box2.y) && (box1.y < box2.y))
	{
		if ((box1.z < box2.z) && (box1.w > box2.z))
		{
			collision = true;
		}
		if ((box1.z < box2.w) && (box1.w > box2.w))
		{
			collision = true;
		}
	}
	return(collision);
}