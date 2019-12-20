#pragma once
#include "Mesh.h"

class Snow :public Mesh
{
private:
	const int vertexCount;
	const glm::vec3 gravity = glm::vec3(0.01f, 0.001f, 0.0f);

	GLuint vertexBufferObject;
	
	glm::mat4 trMatrix = glm::mat4(1.0f);
	glm::mat4 rmMatrix = glm::mat4(1.0f);
	

	float fSpeed;

	std::array<UVVertex, 100> vCube;
public:
	Snow();
	virtual ~Snow();
	
	Snow(const Snow& t) = delete;	
	Snow& operator=(const Snow& t) = delete;
	
	Snow(Snow&& rval) = delete;
	Snow& operator=(Snow&& t) = delete;

	void Create();
	void Update(const GLuint& sObj)final;
	
	void Draw(const GLuint& sObj)final;
	void Draw(const float& elapsedTime, const GLuint& sObj) final{}
	
	void SetSpeed(const float& speed);
	void SetPosition(const glm::vec3& pos);
	void MoveDown(const float& fTimeElapsed);


};