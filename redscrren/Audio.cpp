#include "Audio.h"
#include "input.h"

float tmp = 0.0f;

void Audio1::update()
{
	audioSystem->update();
}

void Audio1::playSound(int sound)
{
	if (sound == 1)
	{
		audioSystem->playSound(trackBackground, 0, false, 0);
	}
	else if (sound == 2)
	{
		audioSystem->playSound(fxoof, 0, false, 0);
	}
	else if (sound == 3)
	{
		audioSystem->playSound(fxbruh, 0, false, 0);

	}
}


void Audio1::Create(const char* file, int sound)
{
	if (sound == 1)
	{
		audioSystem->createSound(file, FMOD_LOOP_NORMAL, 0, &trackBackground);
	}
	else if (sound == 2)
	{
		audioSystem->createSound(file, FMOD_DEFAULT, 0, &fxoof);
	}
	else if (sound == 3)
	{
		audioSystem->createSound(file, FMOD_DEFAULT, 0, &fxbruh);


	}
}

bool Audio1::AudioInit()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&audioSystem);
	if (result != FMOD_OK)
	{
		return (false);
	}
	result = audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK)
	{
		return(false);
	}
	return(true);
}

Audio1::Audio1()
{
}

Audio1::~Audio1()
{
}
