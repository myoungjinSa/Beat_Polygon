#pragma once
#include "Mesh.h"

class Snow :public Mesh
{
public:
	const int vertexCount =6 ;
	const glm::vec3 gravity = glm::vec3(0.01f, 0.001f, 0.0f);

public:

	GLuint vertexBufferObject;
	GLuint elementBufferObject;
	glm::mat4 trMatrix = glm::mat4(1.0f);
	glm::mat4 rmMatrix = glm::mat4(1.0f);
	std::array<UVVertex, 100> vCube;

	float fSpeed;
public:
	Snow();
	Snow(const Snow& t) = delete;
	virtual ~Snow();
	
	Snow& operator=(const Snow& t) = delete;
	
	void Create();
	void Update(const GLuint& sObj)final;
	
	void Draw(const GLuint& sObj)final;
	void Draw(const float& elapsedTime, const GLuint& sObj) final{}
	
	void SetSpeed(const float& speed);
	void SetPosition(const glm::vec3& pos);
	void MoveDown(const float& fTimeElapsed);


};