#include "stb_image.h"
#include "stdafx.h"

#include "AlphaBlock.h"

AlphaBlock::AlphaBlock()
{

}

AlphaBlock::~AlphaBlock()
{

}


void AlphaBlock::SetPosition(const glm::vec3& pos)
{

	trMatrix[3].x = pos.x;
	trMatrix[3].y = pos.y;
	trMatrix[3].z = pos.z;

}

void AlphaBlock::Create(GLuint sObj)
{
	//front
	vCube[0] = UVColorVertex(glm::vec3(-2.0f, 3.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[1] = UVColorVertex(glm::vec3(-2.0f, 0.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[2] = UVColorVertex(glm::vec3(2.0f, 3.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			


	vCube[3] = UVColorVertex(glm::vec3(2.0f, 3.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[4] = UVColorVertex(glm::vec3(-2.0f, 0.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[5] = UVColorVertex(glm::vec3(2.0f, 0.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	//left
	vCube[6] = UVColorVertex(glm::vec3(-2.0f, 3.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[7] = UVColorVertex(glm::vec3(-2.0f, 3.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[8] = UVColorVertex(glm::vec3(-2.0f, 0.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			


	vCube[9] = UVColorVertex(glm::vec3(-2.0f, 3.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[10] = UVColorVertex(glm::vec3(-2.0f, 0.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[11] = UVColorVertex(glm::vec3(-2.0f, 0.f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	//back
	vCube[12] = UVColorVertex(glm::vec3(-2.0f, 3.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[13] = UVColorVertex(glm::vec3(2.0f, 3.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[14] = UVColorVertex(glm::vec3(-2.0f, 0.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			


	vCube[15] = UVColorVertex(glm::vec3(2.0f, 3.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[16] = UVColorVertex(glm::vec3(2.0f, 0.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[17] = UVColorVertex(glm::vec3(-2.0f, 0.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			

	//right
	vCube[18] = UVColorVertex(glm::vec3(2.0f, 3.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[19] = UVColorVertex(glm::vec3(2.0f, 3.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[20] = UVColorVertex(glm::vec3(2.0f, 0.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			


	vCube[21] = UVColorVertex(glm::vec3(2.0f, 3.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[22] = UVColorVertex(glm::vec3(2.0f, 0.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[23] = UVColorVertex(glm::vec3(2.0f, 0.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			

	//top
	vCube[24] = UVColorVertex(glm::vec3(2.0f, 3.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[25] = UVColorVertex(glm::vec3(-2.0f, 3.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[26] = UVColorVertex(glm::vec3(-2.0f, 3.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(0.0f, 0.0f));			


	vCube[27] = UVColorVertex(glm::vec3(2.0f, 3.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[28] = UVColorVertex(glm::vec3(-2.0f, 3.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[29] = UVColorVertex(glm::vec3(2.0f, 3.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	//bottom
	vCube[30] = UVColorVertex(glm::vec3(-2.0f, 0.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[31] = UVColorVertex(glm::vec3(2.0f, 0.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[32] = UVColorVertex(glm::vec3(2.0f, 0.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			


	vCube[33] = UVColorVertex(glm::vec3(-2.0f, 0.0f, -2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[34] = UVColorVertex(glm::vec3(2.0f, 0.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f),glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[35] = UVColorVertex(glm::vec3(-2.0f, 0.0f, 2.0f),glm::vec4(1.0f,1.0f,1.0f,0.5f), glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vCube.size() * sizeof(UVColorVertex), &vCube, GL_STATIC_DRAW);

	CreateTexture(sObj);
}

void AlphaBlock::CreateTexture(GLuint sObj)
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

	unsigned char* data = stbi_load("ice1.png", &widthImage, &heightImage, &numberOfChannel,0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	int tLocation_1 = glGetUniformLocation(sObj, "texture1"); 
	glUniform1i (tLocation_1, 0); 
}
void AlphaBlock::Update(const GLuint& sObj)
{

	worldTransform = trMatrix * rmMatrix;
	
	unsigned int WT = glGetUniformLocation(sObj, "WorldTransform");

	glUniformMatrix4fv(WT, 1, GL_FALSE, glm::value_ptr(worldTransform));
}	
void AlphaBlock::Draw(const GLuint & sObj)
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
	
	glDrawArrays(GL_TRIANGLES, 0,36);


	glDisableVertexAttribArray(attribPos);
	glDisableVertexAttribArray(attribCol);
	glDisableVertexAttribArray(attribNorm);
	glDisableVertexAttribArray(attribUV);


	glBindBuffer(GL_ARRAY_BUFFER, 0);


	
}