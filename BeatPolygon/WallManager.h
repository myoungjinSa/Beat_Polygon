#pragma once

#include "Wall.h"


constexpr int blockCount = 100;

class Wall;

class WallManager 
{
	
	
	std::array<Wall, blockCount> walls;
public:
	WallManager();
	~WallManager();


	void Create(const GLuint& sObj);
	void Update(float time);
	void Draw(GLuint& sObj);

};