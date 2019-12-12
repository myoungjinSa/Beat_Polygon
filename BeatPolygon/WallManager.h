#pragma once
#include"Wall.h"
#include <fstream>
 
class Light;
class Wall;

class WallManager 
{
	
	std::vector<Wall> walls;

	std::ofstream fp;
	std::ifstream in;
	std::string time;
	std::vector<float> nodeTimeVector;


public:
	WallManager();
	~WallManager();

#ifdef WRITE_MUSIC
	void OpenMusicFile();
	void WriteMusicInfo(float time);
	void CloseMusicFile();
#else

	void ReadMusicFile();
#endif
	void Create(const GLuint& sObj,const GLuint& sParticleShaderObj);
	void Update(const float& time,Light* pLight);
	void Draw(const float& elapsedTime,const GLuint& sObj);
	

	volatile bool CheckCollision(Light* player, Wall* pWall);
	void ProcessCollision(Wall& wall);

public:
	int blockCount{0};

};