#pragma once
#include "Mesh.h"

class ScreenEffect : public Mesh
{
public:
	ScreenEffect();
	virtual ~ScreenEffect();

	
	void Create(const GLuint& sObj,const char* image,const char* image2);
	void Update(const GLuint& sObj);

	void Draw(const GLuint& sObj);
	void Draw(const float& elapsedTime,const GLuint& sObj)final{}

	void CreateTexture(GLuint sObj,const char* texture1,const char* texture2);
	void IsGameStart(bool texture);

public:
	bool isGameStart{ false };
private:
	glm::mat4 trMatrix = glm::mat4(1.0f);
	glm::mat4 rmMatrix = glm::mat4(1.0f);
	glm::mat4 scMatrix = glm::mat4(1.0f);

	glm::mat4 worldTransform = glm::mat4(1.0f);

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	std::array<UVAlphaVertex, 6> aSquare;

	GLuint sampler;
	GLuint texture[2];
	GLuint shaderObject;
	GLuint vertexBufferObject;

	const int vCount = 8;

};