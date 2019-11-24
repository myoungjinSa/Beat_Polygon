#include "stdafx.h"
#include "Cube.h"

Cube::Cube(Vertex v0,Vertex v1,Vertex v2,Vertex v3,Vertex v4,Vertex v5,Vertex v6,Vertex v7)
	:v0{v0},v1{v1},v2{v2},v3{v3},v4{v4},v5{v5},v6{v6},v7{v7},vCount{8},indexCount{36}
{

	

	for(int i =0;i<indexCount ; ++i)
	{
		Indices[i] = 0;
	}

	std::cout << "Cube »ı¼º" << std::endl;
}
Cube::~Cube()
{
	std::cout << "Cube ¼Ò¸ê" << std::endl;
}


void Cube::Update(const GLuint& sObj)
{


	glm::mat4 worldTransform = trMatrix * rmMatrix;

	unsigned int WT = glGetUniformLocation(sObj, "WorldTransform");

	glUniformMatrix4fv(WT, 1, GL_FALSE, glm::value_ptr(worldTransform));
}	

void Cube::Draw(const GLuint & sObj)
{
	Update(sObj);
	int attribPos = glGetAttribLocation(sObj, "vPos");
	int attribCol = glGetAttribLocation(sObj, "vColor");
	glEnableVertexAttribArray(attribPos);
	glEnableVertexAttribArray(attribCol);


	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
	glVertexAttribPointer(attribCol, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	glDisableVertexAttribArray(attribPos);
	glDisableVertexAttribArray(attribCol);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

