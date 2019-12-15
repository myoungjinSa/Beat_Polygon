#pragma once
#include "Mesh.h"

class Particle : public Mesh
{
public:
	glm::mat4 trMatrix = glm::mat4(1.0f);
	glm::mat4 rmMatrix = glm::mat4(1.0f);
	glm::mat4 scMatrix = glm::mat4(1.0f);

	glm::mat4 worldTransform = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
	std::array<Diffuse_Vertex, 36> vCube;


public:

	Particle();
	virtual ~Particle();
	void Create(GLuint sObj,const glm::vec3& movingDir,glm::vec3 color);
	void InitShader(GLuint shaderObj);
	void Update(const GLuint& sObj) {}
	void UpdatePos(const float& elapsedTime,const GLuint &sObj);
	//void Draw(const float& elapsedTime,const GLuint & sObj,const glm::vec3& position);
	void Draw(const GLuint & sObj) {}
	void Draw(const float& elapsedTime, const GLuint & sObj);
	void SetPosition(const glm::vec3 & pos);
	glm::vec3 GetPosition();

public:
	GLuint shaderObject;
	GLuint vertexBufferObject;
	GLuint elementBufferObject;
	const int vCount = 8;
	const int indexCount = 36;


	float maxExplosionDuration{ 0.0f };
	float fSpeed{0.0f};
	const glm::vec3 gravity{ 0.0f,-1.0f,0.0f };
	glm::vec3 movingDirection{ 0.0f,0.0f,0.0f };

	float explosionTime{ 0.0f };

};
