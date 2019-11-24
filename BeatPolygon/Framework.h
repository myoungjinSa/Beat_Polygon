#pragma once

class Cube;
class Camera;

class Framework
{
private:
	GLuint shaderProgram;

	const float fWindowWidth = 800.0f;
	const float fWindowHeight = 600.0f;

	Cube* pCube{ nullptr };


public:
	Framework()
	{
		
	}
	~Framework();

	void CreateCube();
	void CreateCamera(glm::vec3 pos,glm::vec3 dir,glm::vec3 up);

	
	void Init(int argc, char** argv);


	bool InitShader();
	void Draw();
	bool CheckProgram(GLuint program);
	GLvoid Reshape(int w, int h);
	const std::string ReadStringFromFile(const std::string& filename);
	GLuint CreateShader(GLenum shaderType, const std::string& source);
public:

	Camera* pCamera{ nullptr };

};