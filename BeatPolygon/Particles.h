#pragma once
#include "Mesh.h"

class Particle : public Mesh
{


public:

	Particle();
	virtual ~Particle();
	void Create(const GLuint& sObj,const glm::vec3& movingDir,const glm::vec3& color);
	void InitShader(const GLuint& shaderObj);
	void Update(const GLuint& sObj)final {}
	void UpdatePos(const float& elapsedTime,const GLuint &sObj);
	void Draw(const GLuint & sObj)final {}
	void Draw(const float& elapsedTime, const GLuint & sObj)final;
	void SetPosition(const glm::vec3 & pos);
	const glm::vec3& GetPosition() const;

private:
	const int vCount = 8;
	const int indexCount = 36;
	const glm::vec3 gravity{ 0.0f,-1.0f,0.0f };
	


private:
	std::array<Diffuse_Vertex, 36> vCube;

	glm::mat4 trMatrix;
	glm::mat4 rmMatrix;
	glm::mat4 scMatrix;

	glm::mat4 worldTransform;
	glm::vec3 position;
	
	glm::vec3 movingDirection;

	GLuint shaderObject;
	GLuint vertexBufferObject;
	GLuint elementBufferObject;
	
	float maxExplosionDuration;
	float fSpeed;
	float explosionTime;

};
