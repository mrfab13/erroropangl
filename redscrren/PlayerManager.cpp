#include "PlayerManager.h"

Input input1;

PlayerManager::PlayerManager()
{

}

PlayerManager::~PlayerManager()
{

}

glm::vec3 PlayerManager::GetObjectPos()
{
	return (objPos);
}

void PlayerManager::SetObjectPos(glm::vec3 temp)
{
	objPos = temp;
}

void PlayerManager::initializeObjPos()
{
	objPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void PlayerManager::setbulletDir(int Dir)
{
	bulletDir = Dir;
}

void PlayerManager::movement(GLfloat deltaTime)
{
	const float speed = 0.05f;
	glm::vec3 temp;
	temp = GetObjectPos();

	if (input1.CheckKeyDown('s') == true)
	{

		if (temp.z < 1.0f)
		{
			temp.z += speed * deltaTime;
			SetObjectPos(temp);

		}

	}
	if (input1.CheckKeyDown('a') == true)
	{
		if (temp.x > -1.0f)
		{
			temp.x -= speed * deltaTime;
			SetObjectPos(temp);

		}
	}
	if (input1.CheckKeyDown('w') == true)
	{
		if (temp.z > -1.0f)
		{
			temp.z -= speed * deltaTime;
			SetObjectPos(temp);

		}
	}
	if (input1.CheckKeyDown('d') == true)
	{
		if (temp.x < 1.0f)
		{
			temp.x += speed * deltaTime;
			SetObjectPos(temp);

		}
	}
	if (input1.CheckKeyDownS(100) == true) //left
	{
		if (input1.CheckKeyDownS(101) == true) //up
		{
			setbulletDir(7);
		}
		else if (input1.CheckKeyDownS(102) == true) //right
		{
			setbulletDir(5);
		}
		else if (input1.CheckKeyDownS(103) == true) //down
		{
			setbulletDir(1);
		}
		else // just 1 dir
		{
			setbulletDir(4);
		}
	}
	else if (input1.CheckKeyDownS(101) == true) //up
	{
		if (input1.CheckKeyDownS(100) == true) //left
		{
			setbulletDir(7);
		}
		else if (input1.CheckKeyDownS(102) == true) //right
		{
			setbulletDir(9);
		}
		else if (input1.CheckKeyDownS(103) == true) //down
		{
			setbulletDir(5);
		}
		else //just 1 dir
		{
			setbulletDir(8);
		}
	}
	else if (input1.CheckKeyDownS(102) == true) //right
	{
		if (input1.CheckKeyDownS(100) == true) //left
		{
			setbulletDir(5);
		}
		else if (input1.CheckKeyDownS(101) == true) //up
		{
			setbulletDir(9);
		}
		else if (input1.CheckKeyDownS(103) == true) //down
		{
			setbulletDir(3);
		}
		else //just 1 dir
		{
			setbulletDir(6);
		}
	}
	else if (input1.CheckKeyDownS(103) == true) //down
	{
		if (input1.CheckKeyDownS(100) == true) //left
		{
			setbulletDir(1);
		}
		else if (input1.CheckKeyDownS(102) == true) //right
		{
			setbulletDir(3);
		}
		else if (input1.CheckKeyDownS(101) == true) //up
		{
			setbulletDir(5);
		}
		else //just 1 dir
		{
			setbulletDir(2);
		}
	}
	else
	{
		setbulletDir(5);
	}
}

void PlayerManager::FIRETHECANNONS_AHHHHHHHHH(GLfloat deltatime, camera* camera1, GLuint program)
{
	reloadTime += deltatime;
	if (reloadTime >= 1.0f)
	{
		reloadTime = 0.0f;

		if (bulletDir != 5 && bulletDir != 0)
		{
			bullets.push_back(new Object(bulletDir, deltatime, objPos, program));
		}
	}
	BulletProcess(deltatime, camera1, program);
	
}

void PlayerManager::BulletProcess(GLfloat deltaTime, camera* camera1, GLuint program)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bool test = bullets.at(i)->Process(deltaTime, camera1, program);
		if (test == false)
		{

			std::vector<Object*> tmp;

			for (int k = 0; k< bullets.size(); k++)
			{
				if (k != i) 
				{
					tmp.push_back(bullets.at(k));
				}
			}

			delete bullets[i];
			bullets.clear();

			for (int k = 0; k < tmp.size(); k++)
			{
				if (k != i)
				{
					bullets.push_back(tmp.at(k));
				}
			}
			tmp.clear();
		}

	}
}






