#pragma once
#include "Timer.h"

class Camera;

class Cube;
class Crane;
class Light;
class Pyramid;
class Snow;
class AlphaBlock;

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

	void CreateTexture();
	void SetTexture();

	void RotateCamera(bool bRot);
	void ObjRotate();

	void Update();
	void DrawRightWall();
	void DrawLeftWall();
	void DrawFloor();
	void Draw();
	GLvoid Reshape(int w, int h);


	void Reset();
	

public:

	Camera* pCamera{ nullptr };
	
	enum class SPIN_DIR {LEFT,RIGHT} baseFloorDir;
	enum class MIDDLE_SPIN_DIR {LEFT,RIGHT} middleFloorDir;
	enum class TOP_SPIN_DIR {LEFT,RIGHT} topFloorDir;

	const int blockCount = 5;
	const int snowCount = 100;
	Snow** pSnow;
	Cube** pCube{ nullptr };
	Cube** pLeftCube{ nullptr };
	Cube** pRightCube{ nullptr };


	AlphaBlock** pBlocks{ nullptr };
	glm::vec3 lightPos{ 2.0f, 5.2f, 1.0f };
	Pyramid* pPyramid{ nullptr };
	Light* pLight{ nullptr };
	Timer timer;
	GLuint GetShaderProgram(int i) { return shaderProgram[i]; }

	bool snowStop{ false };
private:
	
	GLuint sampler;
	GLuint texture1;
	GLuint shaderProgram[3];

	
	bool bMiddleRotate{ false };
	
	const int cubeCount{ 10 };
	int fWindowWidth{ 800 };
	int fWindowHeight{ 600 };
};