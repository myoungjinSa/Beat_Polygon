#include "stdafx.h"
#include "WallManager.h"
#include "Framework.h"
#include "Light.h"
#include <chrono>



WallManager::WallManager()
{

}

WallManager::~WallManager()
{

}

void WallManager::Create(const GLuint& sObj,const GLuint& sParticleShaderObj)
{
	
	
	
	int division = 3;
	std::uniform_real_distribution<double>uxd(-13.0f, 13.0f);

	std::random_device rd;
	std::default_random_engine dre(rd());


	for (int i = 0; i < blockCount; ++i)
	{
	
		walls[i].Create(sObj,2.0f,2.0f,2.0f);
		walls[i].SetPosition(glm::vec3(uxd(dre), 3.5f, -15.0f * (i + 1)));
		walls[i].InitParticleShader(sParticleShaderObj);
	}



}

void WallManager::Update(const float& time, Light* player)
{

	for (int i = 0; i < blockCount; ++i)
	{
		
		walls[i].Move(time);
		if(CheckCollision(player, &walls[i]))
		{

			ProcessCollision(walls[i]);
		}

	}

}

void WallManager::ProcessCollision(Wall& wall)
{
	if (wall.b_Blowing == false)
	{

		wall.SaveExplosionPos(wall.GetPosition());
		wall.b_Blowing = true;
		Framework::hitCount += 1;

	}
	
}
volatile bool WallManager::CheckCollision(Light* player,Wall* pWall)
{
	volatile bool bCollision{ false };
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
		walls[i].Draw(elapsedTime,sObj);
	}
	
}