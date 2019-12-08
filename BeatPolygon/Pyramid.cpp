#include "stb_image.h"

#include "stdafx.h"
#include "Pyramid.h"

Pyramid::Pyramid()
{

}

Pyramid::~Pyramid()
{

}
void Pyramid::SetPosition(const glm::vec3& pos)
{

	trMatrix[3].x = pos.x;
	trMatrix[3].y = pos.y;
	trMatrix[3].z = pos.z;

}

void Pyramid::Create(GLuint sObj)
{
	//front
	vPyramid[0] = UVColorVertex(glm::vec3(0.0f, 2.0f, 0.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(0.0f,1.0f,0.0f), glm::vec2(0.5f, 1.0f));			//left Top
	vPyramid[1] = UVColorVertex(glm::vec3(-1.5f, -0.5f, 1.5f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			//left Bottom
	vPyramid[2] = UVColorVertex(glm::vec3(1.5f, -0.5f, 1.5f), glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			//right top
	
	//left
	vPyramid[3] = UVColorVertex(glm::vec3(0.0f, 2.0f, 0.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(0.0f,1.0f,0.0f), glm::vec2(0.5f, 1.0f));			//right bottom
	vPyramid[4] = UVColorVertex(glm::vec3(-1.5f, -0.5f, -1.5f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			
	vPyramid[5] = UVColorVertex(glm::vec3(-1.5f, -0.5f, 1.5f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));


	//back
	vPyramid[6] = UVColorVertex(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(0.0f,1.0f,0.0f), glm::vec2(0.5f, 1.0f));
	vPyramid[7] = UVColorVertex(glm::vec3(1.5f, -0.5f, -1.5f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));
	vPyramid[8] = UVColorVertex(glm::vec3(-1.5f, -0.5f, -1.5f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));
	
	//right
	vPyramid[9] = UVColorVertex(glm::vec3(0.0f, 2.0f, 0.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(0.0f,1.0f,0.0f), glm::vec2(0.5f, 1.0f));
	vPyramid[10] = UVColorVertex(glm::vec3(1.5f, -0.5f, 1.5f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));
	vPyramid[11] = UVColorVertex(glm::vec3(1.5f, -0.5f, -1.5f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));
	

	//bottom
	vPyramid[12] = UVColorVertex(glm::vec3(1.5f, -0.5f, 1.5f), glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(1.0f, 1.0f));		//left+Z
	vPyramid[13] = UVColorVertex(glm::vec3(-1.5f, -0.5f, 1.5f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(0.0f, 1.0f));		//right+Z
	vPyramid[14] = UVColorVertex(glm::vec3(1.5f, -0.5f, -1.5f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));		//left-Z
	
	vPyramid[15] = UVColorVertex(glm::vec3(-1.5f, -0.5f, 1.5f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(0.0f, 1.0f));		//right-Z
	vPyramid[16] = UVColorVertex(glm::vec3(-1.5f, -0.5f, -1.5f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));		//right-Z
	vPyramid[17] = UVColorVertex(glm::vec3(1.5f, -0.5f, -1.5f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));		//right-Z

	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vPyramid.size() * sizeof(UVColorVertex), &vPyramid, GL_STATIC_DRAW);

	CreateTexture(sObj);

}
void Pyramid::CreateTexture(GLuint sObj)
{
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT,16.0f);

	
	stbi_set_flip_vertically_on_load(true); 
	int widthImage, heightImage, numberOfChannel;

	

	//텍스쳐 이름 생성
	glGenTextures(1, &texture1);
	
	//이제 GL_TEXTURE_2D 바인딩 포인트를 사용하여 콘텍스트에 바인딩 한다.
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load("ice3.png", &widthImage, &heightImage, &numberOfChannel,0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	int tLocation_1 = glGetUniformLocation(sObj, "texture1"); 
	glUniform1i (tLocation_1, 0); 
	

}
void Pyramid::Draw(const GLuint& sObj)
{
	Update(sObj);
	

	int attribPos = glGetAttribLocation(sObj, "vPos");
	int attribCol = glGetAttribLocation(sObj, "vColor");
	int attribNorm = glGetAttribLocation(sObj, "vNormal");
	int attribUV = glGetAttribLocation(sObj, "vUV");

	glEnableVertexAttribArray(attribPos);
	glEnableVertexAttribArray(attribCol);
	glEnableVertexAttribArray(attribNorm);
	glEnableVertexAttribArray(attribUV);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	
	

	glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), nullptr);
	glVertexAttribPointer(attribCol, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(attribNorm, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(7 * sizeof(float)));
	glVertexAttribPointer(attribUV, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(10 * sizeof(float)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	
	glDrawArrays(GL_TRIANGLES, 0,18);


	glDisableVertexAttribArray(attribPos);
	glDisableVertexAttribArray(attribCol);
	glDisableVertexAttribArray(attribNorm);
	glDisableVertexAttribArray(attribUV);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Pyramid::Update(const GLuint& sObj)
{
	
	worldTransform = trMatrix * rmMatrix;
	
	unsigned int WT = glGetUniformLocation(sObj, "WorldTransform");

	glUniformMatrix4fv(WT, 1, GL_FALSE, glm::value_ptr(worldTransform));
}