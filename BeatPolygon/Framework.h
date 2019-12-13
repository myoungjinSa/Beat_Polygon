#pragma once
#include "Timer.h"

class Camera;
class Cube;
class Crane;
class Light;
class Pyramid;
class Snow;
class AlphaBlock;
class WallManager;
class UI;
class UIManager;
class GAMESOUND;
class ScreenEffect;

constexpr int shaderCount = 4;


class Framework
{
public:
	Framework();
	~Framework();

	void CreateCamera(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);
	void Init(int argc, char** argv);
	bool InitShader();
	void CreateSnow();
	bool CheckProgram(GLuint program);
	GLuint CreateShader(GLenum shaderType, const std::string& source);
	const std::string ReadStringFromFile(const std::string& filename);
	void CreateCube();
	void CreatePyramid();
	void CreateLight();
	void CreateBlocks();
	void CreateLeftCube();
	void CreateRightCube();
	void CreateCeiling();
	void CreateWallManager();
	void CreateSound();
	void CreateScreenEffect();
	void CreateTexture();
	void SetTexture();
	void AddFont();

	void CheckCollision();
	void RotateCamera(bool bRot);
	void Update();
	void DrawRightWall();
	void DrawLeftWall();
	void DrawCeiling();
	void DrawFloor();
	void DrawFont();
	void Draw();
	GLvoid Reshape(int w, int h);
	void StartDash();
	void EndDash();
public:

	Camera* pCamera{ nullptr };
	
	enum class SPIN_DIR { LEFT, RIGHT } baseFloorDir;
	enum class MIDDLE_SPIN_DIR { LEFT, RIGHT } middleFloorDir;
	enum class TOP_SPIN_DIR { LEFT, RIGHT } topFloorDir;

	const int blockCount = 5;
	const int snowCount = 100;
	Snow** pSnow;
	Cube** pCube{ nullptr };
	Cube** pLeftCube{ nullptr };
	Cube** pRightCube{ nullptr };
	Cube** pCeiling{ nullptr };

	static unsigned short hitCount;


	AlphaBlock** pBlocks{ nullptr };
	glm::vec3 lightPos{ 2.0f, 5.2f, 1.0f };
	Pyramid* pPyramid{ nullptr };
	Light* pLight{ nullptr };
	Timer timer;
	
	GLuint GetShaderProgram(int i) { return shaderProgram[i]; }

	bool snowStop{ false };
	WallManager* pWallManager{ nullptr };
	std::unique_ptr<ScreenEffect> screenEffect;
	std::unique_ptr<GAMESOUND> gameSound;
	std::unique_ptr<UIManager> uiManager;
private:

	struct MapInfo 
	{
		float leftPos;
		float rightPos;
		float upPos;
		float downPos;

		MapInfo() :leftPos{ 0.0f }, rightPos{ 0.0f }, upPos{ 0.0f }, downPos{ 0.0f }{}
	}mapInfo;

	GLuint sampler;
	GLuint texture1;
	GLuint shaderProgram[shaderCount];

	
	unsigned short keyCombination{0};
	


	bool bMiddleRotate{ false };
	
	const int cubeCount{ 10 };
	int fWindowWidth{ 1200 };
	int fWindowHeight{ 720 };
};