#include "Input.h"



using namespace std;
Input input2;


enum InputState
{
	INPUT_UP,
	INPUT_DOWN,
	INPUT_UP_FIRST,
	INPUT_DOWN_FIRST,
};

InputState KeyState[255];
InputState KeyState_S[255];



Input::Input()
{
}

Input::~Input()
{
}


Input copyinputclass()
{
	return(input2);
}

bool Input::CheckKeyDown(int key)
{
	if (KeyState[key] == INPUT_DOWN)
	{

		return(true);
	}
	return(false);
}

bool Input::CheckKeyDownS(int key)
{
	if (KeyState_S[key] == INPUT_DOWN)
	{

		return(true);
	}
	return(false);
}

int Input::inputdelay(Input& input)
{
	if (input2.delay ==1)
	{
		input.delay++;
	}
	if (input2.delay == 2)
	{
		input.delay = 0;

	}
	return (input.delay);
}

bool Input::checkDownFirst(Input& input, unsigned char key)
{
	input.delay = inputdelay(input);

	if (input.delay > 2)
	{
		input.firstDown = false;
	}
	else 
	{
		input.firstDown = true;
	}

	return (input.firstDown);
}




void Input::KeyboardDown(unsigned char key, int x, int y)
{
	
	KeyState[key] = INPUT_DOWN;
	input2.delay = 1;
}

void Input::KeyboardUp(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_UP;
	input2.delay = 2;
}

void Input::specialCharDown(int key, int x, int y)
{
	KeyState_S[key] = INPUT_DOWN;
	input2.delay = 1;

}

void Input::specialCharUp(int key, int x, int y)
{
	KeyState_S[key] = INPUT_UP;
	input2.delay = 2;

}


