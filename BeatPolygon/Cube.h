#pragma once
#include "Mesh.h"

class Cube : public Mesh
{

public:
	glm::mat4 trMatrix = glm::mat4(1.0f);
	glm::mat4 rmMatrix = glm::mat4(1.0f);
	glm::mat4 scMatrix = glm::mat4(1.0f);

	glm::mat4 worldTransform = glm::mat4(1.0f);

	glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
	std::array<UVVertex, 36> vCube;

	int id;
public:

	Cube();
	virtual ~Cube();

	void CreateTexture(const GLuint& sObj,const char* textureName);
	void Create(const GLuint& sObj);
	
	void Update(const GLuint &sObj);
	void Draw(const GLuint & sObj);
	void Draw(const float& elapsedTime, const GLuint& sObj) {}
	
	void SetID(const int& i);
	void SetPosition(const glm::vec3 & pos);

	const glm::vec3 GetPosition() const;

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