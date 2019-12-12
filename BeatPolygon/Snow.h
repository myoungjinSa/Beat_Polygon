#pragma once
#include "Mesh.h"

class Snow :public Mesh
{
public:


	GLuint vertexBufferObject;
	GLuint elementBufferObject;

	glm::vec3 gravity = glm::vec3(0.01f, 0.001f, 0.0f);

	glm::mat4 trMatrix = glm::mat4(1.0f);
	glm::mat4 rmMatrix = glm::mat4(1.0f);
	std::array<UVVertex, 100> vCube;

	const int vertexCount =6 ;
	//unsigned int indices[6];
	float fSpeed{0.0f};
public:
	Snow() {};
	Snow(const Snow& t) = delete;

	Snow& operator=(const Snow& t) = delete;

	void Update(const GLuint& sObj)final;
	//void Draw(const GLuint& sObj, const GLuint& vbo,const GLuint)final {}
	void Draw(const GLuint& sObj)final;
	void Draw(const float& elapsedTime, const GLuint& sObj) {}
	//void Draw(const float& elapsedTime, const GLuint & sObj, const glm::vec3& position){}
	void SetSpeed(float speed);
	void SetPosition(const glm::vec3& pos);
	void MoveDown(float fTimeElapsed);

	void Create();

	virtual ~Snow()
	{
		std::cout << "Square ¼Ò¸ê" << std::endl;
		
	}

};