#include "stdafx.h"
#include "WallManager.h"

WallManager::WallManager()
{

}

WallManager::~WallManager()
{

}

void WallManager::Create(const GLuint& sObj)
{
	
	
	
	int division = 3;
	std::uniform_real_distribution<double>uxd(-14.0f, 14.0f);
	std::uniform_real_distribution<double>uyd(1.0f, 11.0f);

	

	std::default_random_engine dre((unsigned int)time(0));

	for (int i = 0; i < blockCount; ++i)
	{
		walls[i].Create(sObj, glm::vec3(uxd(dre),uyd(dre),-15.0f * i),2.0f,2.0f,2.0f);

	}



}

void WallManager::Update(float time)
{

	for (int i = 0; i < blockCount; ++i)
	{
		walls[i].Move(time);
			
	}
	
}

void WallManager::Draw(GLuint& sObj)
{

	

	for (int i = 0; i < blockCount; ++i)
	{
	
		walls[i].Draw(sObj);
	}
	
}