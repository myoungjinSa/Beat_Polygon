#include "stdafx.h"
#include "Light.h"
#include "Camera.h"


Light::Light(const Diffuse_Vertex& v0,const Diffuse_Vertex& v1,const Diffuse_Vertex& v2,const Diffuse_Vertex& v3,const Diffuse_Vertex& v4,const Diffuse_Vertex& v5,const Diffuse_Vertex& v6,const Diffuse_Vertex& v7)
	:shaderObject{ 0 }, fSpeed{ 0.0f }, width{ 0.0f }, height{ 0.0f }, depth{ 0.0f }, fRange{ 0.0f }
	,trMatrix {glm::mat4(1.0f)},rmMatrix{glm::mat4(1.0f)},scMatrix{glm::mat4(1.0f)},worldTransform{glm::mat4(1.0f)}
	,v0{v0},v1{v1},v2{v2},v3{v3},v4{v4},v5{v5},v6{v6},v7{v7},Indices{0},bDash{false}
	,position{glm::vec3(0.0f,0.0f,0.0f)}
	,vertexBufferObject{0}
	,elementBufferObject{0}
	,dir{DIRECTION::STOP}
	,vCount{8}
	,indexCount{36}
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
void Light::SetRange(const float& range)
{
	fRange = range;
}
void Light::SetSpeed(const float& speed)
{
	fSpeed = speed;

}

void Light::InitShader(const GLuint& shaderObj)
{
	shaderObject = shaderObj;
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
void Light::SetWidth(const float& w)
{
	width = w ;
}

void Light::SetHeight(const float& h)
{
	height = h;
}

void Light::SetDepth(const float& d)
{
	depth = d;
}
const float& Light::GetDepth() const { return depth; }
const float& Light::GetWidth() const { return width; }
const float& Light::GetHeight() const { return height; }
const float& Light::GetSpeed() const { return fSpeed; }

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

