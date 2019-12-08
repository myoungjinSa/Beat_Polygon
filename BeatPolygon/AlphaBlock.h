#pragma once

#include "Mesh.h"

class AlphaBlock : public Mesh
{
public:
	glm::mat4 trMatrix = glm::mat4(1.0f);
	glm::mat4 rmMatrix = glm::mat4(1.0f);
	glm::mat4 scMatrix = glm::mat4(1.0f);

	glm::mat4 worldTransform = glm::mat4(1.0f);

	glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
	std::array<UVColorVertex, 36> vCube;
	int id;
public:
	AlphaBlock();
	virtual ~AlphaBlock();

	void InitShader(GLuint shaderObj);
	void Update(const GLuint &sObj);
	void Draw(const GLuint & sObj);
	void CreateTexture(GLuint sObj);
	void Create(GLuint sObj);
	void SetID(int i) { id = i; }
	void SetPosition(const glm::vec3 & pos);

	glm::vec3 GetPosition();

public:
		
	GLuint sampler;
	GLuint texture1;
	GLuint shaderObject;
	GLuint vertexBufferObject;
	GLuint elementBufferObject;

	unsigned int Indices[36];

	const int vCount = 8;
	const int indexCount = 36;
};