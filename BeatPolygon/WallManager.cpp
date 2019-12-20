#include "stdafx.h"
#include "WallManager.h"
#include "Framework.h"
#include "Wall.h"
#include "Light.h"
#include "Timer.h"
#include "Sound.h"
#include <string>


WallManager::WallManager()
	:blockCount{ 0 }
{

}

WallManager::~WallManager()
{

#ifdef _WRITE_MUSIC
	if (fp.is_open())
	{
		fp.close();
	}
#endif
}


void WallManager::Create(const GLuint& sObj,const GLuint& sParticleShaderObj)
{
	
	
	
	int division = 3;
	std::uniform_real_distribution<double>uxd(-13.0f, 13.0f);
	std::random_device rd;
	std::default_random_engine dre(rd());


	for (int i = 0; i < blockCount; ++i)
	{
	
		walls[i].Create(sObj,2.0f,2.0f,4.0f);
		walls[i].SetPosition(glm::vec3(uxd(dre), 3.5f, -15.0f * 5.0f));
		walls[i].InitParticleShader(sParticleShaderObj);
	}



}
#ifndef WRITE_MUSIC
void WallManager::ReadMusicFile()
{
	in.open("../BeatPolygon/rythm/piano.txt");


	if(in.is_open())
	{
		while(std::getline(in,time))
		{

			//std::cout << time << std::endl;
			nodeTimeVector.emplace_back(std::stof(time));
		}
	}
	else
	{
		std::cout << "파일이 열리지 않았습니다.\n";
	}
	in.close();


	blockCount = nodeTimeVector.size();
	walls.reserve(blockCount+1);

	for (int i = 0; i < blockCount; ++i)
	{

		walls.emplace_back(Wall{});
	}
}
#endif

#ifdef WRITE_MUSIC
void WallManager::OpenMusicFile()
{

	fp.open("../BeatPolygon/rythm/piano.txt");
	

	
}
void WallManager::WriteMusicInfo(float time)
{
	this->time = std::to_string(time);

	
	std::chrono::steady_clock::time_point currTime = std::chrono::steady_clock::now();

	//std::chrono::steady_clock::time_point elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - elapsedTime)

	std::chrono::milliseconds milli = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - Timer::musicStartTime);
	std::chrono::duration<float> t = milli;

	//std::cout << t.count() << std::endl;

	if (fp.is_open())
	{
		fp << t.count() << std::endl;

	}
}

void WallManager::CloseMusicFile()
{
	if (fp.is_open())
	{
		fp.close();
	}
}
#endif
void WallManager::Update(const float& time, Light* player,const std::unique_ptr<GameSound>& uniqueSound)
{
	
	std::chrono::steady_clock::time_point currTime = std::chrono::steady_clock::now();
	std::chrono::milliseconds elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - Timer::musicStartTime);
	std::chrono::duration<float> t = elapsedTime;

	static int nodeIndex = 0;
	

#ifndef WRITE_MUSIC
	if(t.count() >= nodeTimeVector[nodeIndex] - 2.5f && nodeIndex < blockCount-1)
	{
		walls[nodeIndex].b_Active = true;
		std::cout << nodeIndex << std::endl;
		nodeIndex++;
		
	}
#endif

	static bool isHit{ false };
	for (int i = 0; i < blockCount; ++i)
	{
		if (walls[i].b_Active == true)
		{
			walls[i].Move(time);
			if (CheckCollision(player, &walls[i]))
			{
				isHit = true;
				ProcessCollision(walls[i]);
			}
			if (walls[i].GetPosition().z >= 1.0f)
			{
				walls[i].b_Active = false;
				isHit = false;
				Framework::combo = 0;

			}
		
		}

	}
#ifndef WRITE_MUSIC
	if(isHit)
	{
		uniqueSound->SetVolume(0, 1.0f);
	}
	else
	{
		uniqueSound->SetVolume(0, 0.0f);
	}
#endif


}

void WallManager::ProcessCollision(Wall& wall)
{
	if (wall.b_Blowing == false)
	{

		wall.SaveExplosionPos(wall.GetPosition());
		wall.b_Blowing = true;
		Framework::hitCount += 1;
		Framework::combo += 1;
		wall.b_Active = false;
	}
	
}
bool WallManager::CheckCollision(const Light* player,const Wall* pWall)
{
	bool bCollision{ false };
	float bonusSize = 0.5f;
	float playerL_X = player->GetPosition().x - player->GetWidth() * 0.5f;
	float playerR_X = player->GetPosition().x + player->GetWidth() * 0.5f;
	float playerT_Y = player->GetPosition().y + player->GetHeight() * 0.5f;
	float playerB_Y = player->GetPosition().y - player->GetHeight() * 0.5f;
	float player_ZMax = player->GetPosition().z - player->GetDepth() * 0.5f;
	float player_ZMin = player->GetPosition().z + player->GetDepth() * 0.5f;

	float blockL_X = pWall->GetPosition().x - (pWall->GetWidth() + bonusSize )* 0.5f;
	float blockR_X = pWall->GetPosition().x + (pWall->GetWidth()+bonusSize) * 0.5f;
	float blockT_Y = pWall->GetPosition().y + (pWall->GetHeight() +bonusSize)* 0.5f;
	float blockB_Y = pWall->GetPosition().y - (pWall->GetHeight() +bonusSize)* 0.5f;
	float block_ZMax = pWall->GetPosition().z - (pWall->GetDepth()+bonusSize) * 0.5f;
	float block_ZMin = pWall->GetPosition().z + (pWall->GetDepth() + bonusSize) * 0.5f;


	if(playerR_X >= blockL_X && playerR_X <= blockR_X 
		&& playerT_Y >= blockB_Y && playerT_Y <= blockT_Y 
		&& player_ZMax <= block_ZMin && player_ZMax >= block_ZMax)
	{
		bCollision = true;
	}
	if(playerR_X >= blockL_X && playerR_X <= blockR_X 
		&& playerT_Y >= blockB_Y && playerT_Y <= blockT_Y 
		&& player_ZMin >= block_ZMax && player_ZMin <= block_ZMin)
	{
		bCollision = true;
	}

	if(playerL_X <= blockR_X && playerL_X >= blockL_X
		&& playerT_Y >= blockB_Y && playerT_Y <=blockT_Y
		&& player_ZMax <= block_ZMin && player_ZMax >= block_ZMax)
	{
		bCollision = true;
	}
	if(playerL_X <= blockR_X && playerL_X >= blockL_X
		&& playerT_Y >= blockB_Y && playerT_Y <=blockT_Y
		&& player_ZMin >= block_ZMax && player_ZMin <= block_ZMin)
	{
		bCollision = true;
	}
	if(blockL_X <= playerR_X && blockL_X >= playerL_X
		&& blockT_Y >= playerB_Y && blockT_Y <=playerT_Y
		&& block_ZMax <= player_ZMin && block_ZMax >= player_ZMax)
	{
		bCollision = true;
	}
	if(blockL_X <= playerR_X && blockL_X >= playerL_X
		&& blockT_Y >= playerB_Y && blockT_Y <=playerT_Y
		&& player_ZMax <= block_ZMin && player_ZMax >= block_ZMax)
	{
		bCollision = true;
	}
	if(blockR_X >= playerL_X && blockR_X <= playerR_X 
		&& blockT_Y >= playerB_Y && blockT_Y <= playerT_Y 
		&& block_ZMax <= player_ZMin && block_ZMax >= player_ZMax)
	{
		bCollision = true;
	}
	if(blockR_X >= playerL_X && blockR_X <= playerR_X 
		&& blockT_Y >= playerB_Y && blockT_Y <= playerT_Y 
		&& player_ZMax <= block_ZMin && player_ZMax >= block_ZMax)
	{
		bCollision = true;
	}

	return bCollision;
}

void WallManager::Draw(const float& elapsedTime,const GLuint& sObj)
{
	for (int i = 0; i < blockCount; ++i)
	{
		walls[i].Draw(sObj);
	}
}


