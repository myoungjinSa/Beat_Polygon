#pragma once

#include "Mesh.h"




class Pyramid : public Mesh
{


private:
	std::array<UVColorVertex, 18> vPyramid;
	//std::array<unsigned int, 54> iPyramid;

public:

	Pyramid();
	virtual ~Pyramid();
	void Draw(const GLuint& sObj)final;
	void Update(const GLuint& sObj)final;
	void SetPosition(const glm::vec3& pos);

	void CreateTexture(GLuint sObj);
	void Create(GLuint sObj);
public:

	glm::mat4 trMatrix = glm::mat4(1.0f);
	glm::mat4 rmMatrix = glm::mat4(1.0f);
	glm::mat4 scMatrix = glm::mat4(1.0f);

	glm::mat4 worldTransform = glm::mat4(1.0f);

	glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);

	GLuint texture1;
	GLuint sampler;

	GLuint vertexBufferObject;
	GLuint elementBufferObject;
};