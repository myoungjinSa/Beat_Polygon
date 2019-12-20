#pragma once
#include "Mesh.h"

class Particle : public Mesh
{


public:

	explicit Particle();
	virtual ~Particle();

	Particle(const Particle& ref) = delete;
	Particle& operator=(const Particle& ref) = delete;

	Particle(Particle&& rval) = default;
	Particle& operator=(Particle&& rval) = default;

	void Create(const GLuint& sObj,const glm::vec3& movingDir,const glm::vec3& color);
	void InitShader(const GLuint& shaderObj);
	void Update(const GLuint& sObj)final;
	void UpdatePos(const float& elapsedTime);
	void Draw(const GLuint & sObj)final;
	
	void SetPosition(const glm::vec3 & pos);
	const glm::vec3& GetPosition() const;

private:

	glm::mat4 trMatrix;
	glm::mat4 rmMatrix;
	glm::mat4 scMatrix;

	glm::mat4 worldTransform;
	glm::vec3 position;
	
	glm::vec3 movingDirection;

	GLuint shaderObject;
	GLuint vertexBufferObject;
	
	float maxExplosionDuration;
	float fSpeed;
	float explosionTime;

	const int vCount;
	const glm::vec3 gravity;

	std::array<Diffuse_Vertex, 36> vCube;

};
