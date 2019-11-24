#pragma once
#include "Mesh.h"

class Cube : public Mesh
{

	
	glm::mat4 trMatrix = glm::mat4(1.0f);
	glm::mat4 rmMatrix = glm::mat4(1.0f);
	glm::mat4 scMatrix = glm::mat4(1.0f);


public:

	Cube() = delete;
	Cube(Vertex v0,Vertex v1,Vertex v2,Vertex v3,Vertex v4,Vertex v5,Vertex v6,Vertex v7);
	~Cube();

	void Update(const GLuint &sObj)final;
	void Draw(const GLuint & sObj) final;

public:
	Vertex v0; Vertex v1; Vertex v2; 
	Vertex v3; Vertex v4; Vertex v5; 
	Vertex v6; Vertex v7;


	GLuint vertexBufferObject;
	GLuint elementBufferObject;

	unsigned int Indices[36];



	const int vCount = 8;
	const int indexCount = 36;

};