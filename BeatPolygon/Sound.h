#pragma once
#include <fmod.h>
#include <mmsystem.h>
#pragma comment(lib,"fmod_vc.lib ")

#define CHANNEL_SOUND 10
#define SOUND_BACKGROUND_MUSIC1 1
#define SOUND_BACKGROUND_MUSIC2 2

//게임 사운드
class GAMESOUND
{
private:
	FMOD_SYSTEM *system;
	FMOD_SOUND *soundFile[2];
	FMOD_CHANNEL *channel[2];
public:
	GAMESOUND();
	
	void Reset_AllSound()
	{

	}
	void Create(const char* filePath);
	
	void PlaySOUND(long Type);
	~GAMESOUND();
};