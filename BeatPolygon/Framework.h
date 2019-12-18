#pragma once
#include "Timer.h"

class Camera;
class Cube;
class Crane;
class Light;
class Pyramid;
class Snow;

class WallManager;
class UI;
class UIManager;
class GameSound;
class ScreenEffect;

constexpr int shaderCount = 4;
constexpr int cubeCount = 10 ;
constexpr int blockCount = 5;
constexpr int snowCount = 100;

class Framework
{
public:
	Framework();
	~Framework();

	void CreateCamera(const glm::vec3& pos,const glm::vec3& dir,const glm::vec3& up);
	void Init(int argc, char** argv);
	bool InitShader();
	void CreateSnow();
	bool CheckProgram(const GLuint& program);
	const GLuint& CreateShader(const GLenum& shaderType, const std::string& source);
	const std::string ReadStringFromFile(const std::string& filename);
	void CreateCube();
	void CreateLight();
	void CreateLeftCube();
	void CreateRightCube();
	void CreateCeiling();
	void CreateWallManager();
	void CreateSound();
	void CreateScreenEffect();
	void CreateTexture();
	void SetTexture();
	void CreateFonts();
	void ChangeGameState(const bool& isStart);
	

	void CheckCollision();
	void RotateCamera(const bool& bRot);
	void Update();
	void DrawRightWall(const GLuint& sObj);
	void DrawLeftWall(const GLuint& sObj);
	void DrawCeiling(const GLuint& sObj);
	void DrawFloor(const GLuint& sObj);
	void DrawFont();
	void Draw();

	void StartDash();
	void EndDash();

	inline const int& GetScreenWidth() const;
	inline const int& GetScreenHeight() const;
	inline const GLuint& GetShaderProgram(const int& i) const;
	inline const GLvoid Reshape(const int& w, const int& h);
public:

	static unsigned short hitCount;
	static unsigned short combo;
public:
	
	enum class GAME_STATE { INTRO, INGAME } gameState;
	enum SHADER_OBJ{TEXTURED_LIGHT,DIFFUSE_COLOR,TEXTURED_ALPHA_LIGHT,TEXTURED_SCREEN} shaderObj;
	//WallManager* pWallManager{ nullptr };
	std::unique_ptr<WallManager> wallManager;
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

	glm::vec3 lightPos;

	unsigned short keyCombination;
	
	std::unique_ptr<ScreenEffect> screenEffect;
	std::unique_ptr<GameSound> gameSound;
	std::unique_ptr<UIManager> uiManager;
	std::unique_ptr<Camera> camera;
	
	Snow** pSnow;
	Cube** pCube;
	Cube** pLeftCube;
	Cube** pRightCube;
	Cube** pCeiling;

	Light* pLight;
	Timer timer;
	
	
	int shaderNumber;
	int fWindowWidth;
	int fWindowHeight;

	bool bMiddleRotate;
};