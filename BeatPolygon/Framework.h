#pragma once


class Framework
{
private:
	GLuint shaderProgram;

	const float fWindowWidth = 800.0f;
	const float fWindowHeight = 600.0f;

public:
	Framework()
	{
		
	}
	~Framework();


	void Init(int argc, char** argv);

	bool InitShader();
	void Draw();
	bool CheckProgram(GLuint program);
	GLvoid Reshape(int w, int h);
	const std::string ReadStringFromFile(const std::string& filename);
	GLuint CreateShader(GLenum shaderType, const std::string& source);

};