#include "Manager.h"

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

