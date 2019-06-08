#pragma once
#include <iostream>
#include <windows.h>
#include <fmod.hpp>


class Audio1
{
	public:
		Audio1();
		~Audio1();
		bool AudioInit();
		void Create(const char* file, int sound);
		void playSound(int sound);
		void update();

	private:

		FMOD::System* audioSystem;
		FMOD::Sound* fxoof;
		FMOD::Sound* fxbruh;
		FMOD::Sound* trackBackground;
};
