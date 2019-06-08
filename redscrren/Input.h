#pragma once
#include <iostream>
#include <freeglut.h>
#include <vector>
#include "PlayerManager.h"
#include "glm.hpp"


class Input 
{

public:
	Input();
	~Input();
	static void KeyboardDown(unsigned char key, int x, int y);
	static void KeyboardUp(unsigned char key, int x, int y);
	static void specialCharDown(int key, int x, int y);
	static void specialCharUp(int key, int x, int y);
	bool CheckKeyDown(int key);
	bool CheckKeyDownS(int key);

	int inputdelay(Input& input);
	


	bool checkDownFirst(Input& input, unsigned char key);


private:


	bool firstDown = true;
	bool firstUp = false;
	int delay = 0;



};

Input copyinputclass();
