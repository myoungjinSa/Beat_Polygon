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
	explicit Framework();
	~Framework();

	Framework(const Framework& ref) = delete;
	const Framework& operator=(const Framework& ref) = delete;

	Framework(Framework&& rval) = delete;
	Framework& operator=(Framework&& rval) = delete;


	void Init(int argc, char** argv);
	bool InitShader();
	bool CheckProgram(const GLuint& program);
	const GLuint& CreateShader(const GLenum& shaderType, const std::string& source);
	std::string ReadStringFromFile(const std::string& filename);
	
	void CreateSnow();
	void CreateCamera(const glm::vec3& pos,const glm::vec3& dir,const glm::vec3& up);
	void CreateCube();
	void CreateLight();
	void CreateLeftCube();
	void CreateRightCube();
	void CreateWallManager();
	void CreateSound();
	void CreateScreenEffect();
	void CreateTexture();
	void SetTexture();
	void CreateFonts();
	void ChangeGameState(const bool& isStart);
	void CheckCollision();
	void Update();
	void DrawRightWall(const GLuint& sObj);
	void DrawLeftWall(const GLuint& sObj);
	void DrawFloor(const GLuint& sObj);
	void DrawFont();
	void Draw();
	void StartDash();
	void EndDash();
	const int& GetScreenWidth() const;
	const int& GetScreenHeight() const;
	const GLuint& GetShaderProgram(const int& i) const;


	
	void DeleteObjects();
	inline const GLvoid Reshape(const int& w, const int& h);
public:

	static unsigned short hitCount;
	static unsigned short combo;

private:

	std::unique_ptr<ScreenEffect> screenEffect;
	std::unique_ptr<GameSound> gameSound;
	std::unique_ptr<UIManager> uiManager;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<WallManager> wallManager;

	

	int shaderNumber;
	int fWindowWidth;
	int fWindowHeight;
	unsigned short keyCombination;
	glm::vec3 lightPos;
	Cube** pCube;
	Cube** pLeftCube;
	Cube** pRightCube;
	Light* pLight;
	Snow** pSnow;
	Timer timer;

	GLuint sampler;
	GLuint texture1;
	GLuint shaderProgram[shaderCount];

	
	struct MapInfo 
	{
		float leftPos;
		float rightPos;
		float upPos;
		float downPos;

		MapInfo() :leftPos{ 0.0f }, rightPos{ 0.0f }, upPos{ 0.0f }, downPos{ 0.0f }{}
	}mapInfo;

public:
	enum class GAME_STATE { INTRO, INGAME } gameState;
	enum SHADER_OBJ{TEXTURED_LIGHT,DIFFUSE_COLOR,TEXTURED_ALPHA_LIGHT,TEXTURED_SCREEN} shaderObj;
	//WallManager* pWallManager{ nullptr };

};