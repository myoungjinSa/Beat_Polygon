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

	void SetWidth(float w);
	void SetHeight(float h);
	void SetDepth(float d);

	float GetWidth() { return width; }
	float GetHeight() { return height; }
	float GetDepth() { return depth; }

	void SetPosition(const glm::vec3& pos);
	glm::vec3 GetPosition() { return position; }
	void SetSpeed(float speed);

	void Move(float time);
	virtual void Update(const GLuint& sObj);
	virtual void Draw(const float& elapsedTime,const GLuint& sObj);
//	virtual void Draw(const float& elapsedTime, const GLuint & sObj, const glm::vec3& position) {}
	virtual void Draw(const GLuint & sObj) {}
	void Create(const GLuint& sObj,float width,float height,float depth);
	void CreateParticles();
	void InitParticleShader(const GLuint& shader);
	void CreateTexture(const GLuint& sObj);
	float Random(float min, float max);
	float Random();
	void SaveExplosionPos(const glm::vec3& pos);


public:
	bool b_Blowing{ false };
	bool b_Active{ false };
private:
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
	float halfWidth{ 0.0f };
	float halfHeight{0.0f};
	float halfDepth{0.0f};
	glm::vec3 explosionPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	float fSpeed{0.0f};
	glm::mat4 trMatrix = glm::mat4(1.0f);
	glm::mat4 rmMatrix = glm::mat4(1.0f);
	glm::mat4 scMatrix = glm::mat4(1.0f);

	glm::mat4 worldTransform = glm::mat4(1.0f);

	glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
};