#include "stdafx.h"
#include "Light.h"
#include "Camera.h"


Light::Light(Diffuse_Vertex v0,Diffuse_Vertex v1,Diffuse_Vertex v2,Diffuse_Vertex v3,Diffuse_Vertex v4,Diffuse_Vertex v5,Diffuse_Vertex v6,Diffuse_Vertex v7)
	:v0{v0},v1{v1},v2{v2},v3{v3},v4{v4},v5{v5},v6{v6},v7{v7}
{

}

Light::~Light()
{
	std::cout << "Light¼Ò¸ê" << std::endl;
}
void Light::SetPosition(const glm::vec3& pos)
{

	trMatrix[3].x = pos.x;
	trMatrix[3].y = pos.y;
	trMatrix[3].z = pos.z;

	position = pos;
}
void Light::SetRange(float range)
{
	fRange = range;
}

void Light::InitShader(GLuint shaderObj)
{
	shaderObject = shaderObj;
}
void Light::Rotate(Camera *camera,float fTimeElapsed)
{
	
	if(dir == DIRECTION::LEFT)
		rmMatrix = glm::rotate(rmMatrix, glm::radians(fTimeElapsed * rotationSpeed), glm::vec3(0.0f, 0.0f, 1.0f));
	else if(dir == DIRECTION::RIGHT)
		rmMatrix = glm::rotate(rmMatrix, glm::radians(fTimeElapsed * -rotationSpeed), glm::vec3(0.0f, 0.0f, 1.0f));
	

	
}
void Light::Update(const GLuint& sObj)
{

	trMatrix[3].x = position.x;
	trMatrix[3].y = position.y;
	trMatrix[3].z = position.z;

	
	worldTransform =  trMatrix*rmMatrix;



	unsigned int WT = glGetUniformLocation(shaderObject, "WorldTransform");

	glUniformMatrix4fv(WT, 1, GL_FALSE, glm::value_ptr(worldTransform));


}

void Light::Draw(const GLuint& sObj)
{
	

	int lightPosLocation = glGetUniformLocation(sObj, "lightPos");
	glUniform3f(lightPosLocation, worldTransform[3].x, worldTransform[3].y, worldTransform[3].z);

	

	int lightColorLocation = glGetUniformLocation(sObj, "lightColor");
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
	
	float lightRange = glGetUniformLocation(sObj, "lightRange");
	glUniform1f(lightRange, fRange);

	//std::cout << worldTransform[3].x << "," << worldTransform[3].y << "," << worldTransform[3].z << std::endl;

	glUseProgram(shaderObject);
	
	Update(shaderObject);
	

	int attribPos = glGetAttribLocation(shaderObject, "vPos");
	int attribCol = glGetAttribLocation(shaderObject, "vColor");
	
	glEnableVertexAttribArray(attribPos);
	glEnableVertexAttribArray(attribCol);
	

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

	
	glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
	glVertexAttribPointer(attribCol, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	glDisableVertexAttribArray(attribPos);
	glDisableVertexAttribArray(attribCol);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	
}

