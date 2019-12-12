#pragma once
#include"Wall.h"

constexpr int blockCount = 30;

class Light;
class Wall;

class WallManager 
{
	
	std::array<Wall, blockCount> walls;
public:
	WallManager();
	~WallManager();


	void Create(const GLuint& sObj,const GLuint& sParticleShaderObj);
	void Update(const float& time,Light* pLight);
	void Draw(const float& elapsedTime,const GLuint& sObj);
	

	volatile bool CheckCollision(Light* player, Wall* pWall);
	void ProcessCollision(Wall& wall);
};