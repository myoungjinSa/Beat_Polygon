#pragma once
#include "Mesh.h"
#include "Particles.h"

class Particle;

constexpr int particleCount = 30;

class Wall : public Mesh
{

public:
	Wall();
	virtual ~Wall();

	virtual void Update(const GLuint& sObj)final;
	virtual void Draw(const float& elapsedTime,const GLuint& sObj)final;
	virtual void Draw(const GLuint & sObj)final {}

	void Move(const float& time);
	void Create(const GLuint& sObj,float width,float height,float depth);
	void CreateParticles();
	void InitParticleShader(const GLuint& shader);
	void CreateTexture(const GLuint& sObj);

	void SaveExplosionPos(const glm::vec3& pos);

	const float& Random(const float& min,const float& max);
	const float& Random();
	void SetPosition(const glm::vec3& pos);
	void SetSpeed(const float& speed);
	void SetWidth(const float& w);
	void SetHeight(const float& h);
	void SetDepth(const float& d);

	const glm::vec3& GetPosition() const { return position; }
	const float& GetWidth() { return width; }
	const float& GetHeight() { return height; }
	const float& GetDepth() { return depth; }

	
public:
	volatile bool b_Blowing{ false };
	bool b_Active{ false };
private:
	std::array<glm::vec3, 4> aColors;
	std::array<UVColorVertex, 36> vCube;
	std::array<Particle, particleCount> aParticles;

	GLuint sampler;
	GLuint texture1;
	GLuint shaderObject;
	GLuint particleShaderObject;
	GLuint vertexBufferObject;
	float width;
	float height;
	float depth;
	float halfWidth;
	float halfHeight;
	float halfDepth;
	float fSpeed;


	glm::mat4 trMatrix;
	glm::mat4 rmMatrix;
	glm::mat4 scMatrix;

	glm::mat4 worldTransform;

	glm::vec3 explosionPosition;
	glm::vec3 position;
};