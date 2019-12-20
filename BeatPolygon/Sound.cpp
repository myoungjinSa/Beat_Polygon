
#include "stdafx.h"
#include "Sound.h"


GameSound::GameSound()
	:
	system{nullptr},
	soundFile{nullptr},
	channel{nullptr},
	musicStart{false}

{
	FMOD_System_Create(&system);
	FMOD_System_Init(system, CHANNEL_SOUND, FMOD_INIT_NORMAL, nullptr);	//�ʱ�ȭ
	
}

GameSound::~GameSound()
{
	FMOD_System_Release(system);
}

void GameSound::SetMusicStart(bool s)
{
	musicStart = s;
}
void GameSound::PlaySOUND(long type)
{
	FMOD_System_PlaySound(system, soundFile[type], nullptr, 0, &channel[type]);//BGM ����

}

void GameSound::Create(const char* filePath)
{
	FMOD_System_CreateSound(system, filePath, FMOD_LOOP_OFF, 0, &soundFile[0]);//��� BGM ����

}

void GameSound::SetVolume(const long& type,const float& volume)
{
	FMOD_Channel_SetVolume(channel[type], volume);
}

