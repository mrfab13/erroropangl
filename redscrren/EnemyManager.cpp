#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::EnemyManager(glm::vec3 modelpos, glm::vec3 modelscale)
{
	Modelpos = modelpos;
	Modelscale = modelscale;

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

glm::vec3 EnemyManager::GetModelpos()
{
	return (Modelpos);
}

glm::vec3 EnemyManager::GetModelscale()
{
	return (Modelscale);
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
	speed = 0.01f;
	dir = 1;
	dir2 = 1;
	Setrandxy(randxy);

}

void EnemyManager::Emovement(GLfloat deltaTime, int type, int Wavecheck)
{

	 //wd
	if (type == 1 && (dir == 1))
	{

		Modelpos.z -= speed * deltaTime * randxy.y * ((float)Wavecheck / 20);
		Modelpos.x += speed * deltaTime * randxy.x * ((float)Wavecheck / 20);

		if (Modelpos.z < -6.4f)
		{
			dir = 4;
			Setrandxy(randxy);

		}
		if (Modelpos.x > 3.9f)
		{
			dir = 2;
			Setrandxy(randxy);

		}
	}



 //aw
		if (type == 1 && dir == 2)
		{
			Modelpos.x -= speed * deltaTime * randxy.x * ((float)Wavecheck / 20);
			Modelpos.z -= speed * deltaTime * randxy.y * ((float)Wavecheck / 20);
			if (Modelpos.x < -3.9f)
			{
				dir = 1;
				Setrandxy(randxy);


			}
			if (Modelpos.z < -6.4f)
			{
				dir = 3;
				Setrandxy(randxy);


			}
		}
  //sa
	
		if (type == 1 && dir == 3)
		{
			Modelpos.z += speed * deltaTime * randxy.y * ((float)Wavecheck / 20);
			Modelpos.x -= speed * deltaTime * randxy.x * ((float)Wavecheck / 20);
			if (Modelpos.z > 1.4f)
			{
				dir = 2;
				Setrandxy(randxy);
			}
			if (Modelpos.x < -3.9f)
			{
				dir = 4;
				Setrandxy(randxy);

			}
		}

  //ds
	
		if (type == 1 && dir == 4)
		{
			Modelpos.x += speed * deltaTime * randxy.x * ((float)Wavecheck / 20);
			Modelpos.z += speed * deltaTime * randxy.y * ((float)Wavecheck / 20);
			if (Modelpos.x > 3.9f)
			{
				dir = 3;
				Setrandxy(randxy);

			}
			if (Modelpos.z > 1.4f)
			{
				dir = 1;
				Setrandxy(randxy);

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





