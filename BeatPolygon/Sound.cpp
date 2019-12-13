
#include "stdafx.h"
#include "Sound.h"


GAMESOUND::GAMESOUND()
{
	FMOD_System_Create(&system);
	FMOD_System_Init(system, CHANNEL_SOUND, FMOD_INIT_NORMAL, nullptr);	//�ʱ�ȭ
	
}

GAMESOUND::~GAMESOUND()
{
	FMOD_System_Release(system);
}

void GAMESOUND::PlaySOUND(long type)
{
	FMOD_System_PlaySound(system, soundFile[type], nullptr, 0, &channel[type]);//BGM ����

}

void GAMESOUND::Create(const char* filePath)
{
	FMOD_System_CreateSound(system, filePath, FMOD_LOOP_OFF, 0, &soundFile[0]);//��� BGM ����

}

void GAMESOUND::SetVolume(long type,float volume)
{
	FMOD_Channel_SetVolume(channel[type], volume);
}

