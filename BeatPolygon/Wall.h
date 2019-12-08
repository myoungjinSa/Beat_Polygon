#pragma once
#include "Mesh.h"

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
	void SetSpeed(float speed);

	void Move(float time);
	virtual void Update(const GLuint& sObj);
	virtual void Draw(const GLuint& sObj);
	void Create(const GLuint& sObj,const glm::vec3& center,float width,float height,float depth);

	void CreateTexture(const GLuint& sObj);

private:
	std::array<UVColorVertex, 36> vCube;
	GLuint sampler;
	GLuint texture1;
	GLuint shaderObject;
	GLuint vertexBufferObject;
	float width;
	float height;
	float depth;

	float fSpeed{0.0f};
	glm::mat4 trMatrix = glm::mat4(1.0f);
	glm::mat4 rmMatrix = glm::mat4(1.0f);
	glm::mat4 scMatrix = glm::mat4(1.0f);

	glm::mat4 worldTransform = glm::mat4(1.0f);

	glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
};