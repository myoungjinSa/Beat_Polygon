#include "stb_image.h"
#include "stdafx.h"

#include "Cube.h"

Cube::Cube()
	
{

	
	std::cout << "Cube 생성" << std::endl;
}
Cube::~Cube()
{
	std::cout << "Cube 소멸" << std::endl;
}
void Cube::SetPosition(const glm::vec3& pos)
{

	trMatrix[3].x = pos.x;
	trMatrix[3].y = pos.y;
	trMatrix[3].z = pos.z;

}


glm::vec3 Cube::GetPosition()
{
	glm::vec3 p = glm::vec3(trMatrix[3].x, trMatrix[3].y, trMatrix[3].z);
	
	return p;
}

void Cube::Create(GLuint sObj)
{
	//front
	vCube[0] = UVVertex(glm::vec3(-15.0f, 0.1f, -30.0f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[1] = UVVertex(glm::vec3(-15.0f, -0.1f, -30.0f),glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[2] = UVVertex(glm::vec3(15.0f, 0.1f, -30.0f), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			


	vCube[3] = UVVertex(glm::vec3(15.0f, 0.1f, -30.0f),glm::vec3(1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[4] = UVVertex(glm::vec3(-15.0f, -0.1f, -30.0f),glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[5] = UVVertex(glm::vec3(15.0f, -0.1f, -30.0f), glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	//left
	vCube[6] = UVVertex(glm::vec3(-15.0f, 0.1f, -30.0f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[7] = UVVertex(glm::vec3(-15.0f, 0.1f, 0.0f),glm::vec3(-1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[8] = UVVertex(glm::vec3(-15.0f, -0.1f, 0.0f), glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			


	vCube[9] = UVVertex(glm::vec3(-15.0f, 0.1f, -30.0f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[10] = UVVertex(glm::vec3(-15.0f, -0.1f, 0.0f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[11] = UVVertex(glm::vec3(-15.0f, -0.1f, -30.0f), glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	//back
	vCube[12] = UVVertex(glm::vec3(-15.0f, 0.1f, 0.0f),glm::vec3(-1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[13] = UVVertex(glm::vec3(15.0f, 0.1f, 0.0f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[14] = UVVertex(glm::vec3(-15.0f, -0.1f, 0.0f), glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			


	vCube[15] = UVVertex(glm::vec3(15.0f, 0.1f, 0.0f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[16] = UVVertex(glm::vec3(15.0f, -0.1f, 0.0f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[17] = UVVertex(glm::vec3(-15.0f, -0.1f, 0.0f), glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			

	//right
	vCube[18] = UVVertex(glm::vec3(15.0f, 0.1f, 0.0f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[19] = UVVertex(glm::vec3(15.0f, 0.1f, -30.0f),glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[20] = UVVertex(glm::vec3(15.0f, -0.1f, 0.0f), glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			


	vCube[21] = UVVertex(glm::vec3(15.0f, 0.1f, -30.0f),glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[22] = UVVertex(glm::vec3(15.0f, -0.1f, -30.0f),glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[23] = UVVertex(glm::vec3(15.0f, -0.1f, 0.0f), glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			

	//top
	vCube[24] = UVVertex(glm::vec3(15.0f, 0.1f, 0.0f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[25] = UVVertex(glm::vec3(-15.0f, 0.1f, 0.0f),glm::vec3(-1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[26] = UVVertex(glm::vec3(-15.0f, 0.1f, -30.0f), glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(0.0f, 0.0f));			


	vCube[27] = UVVertex(glm::vec3(15.0f, 0.1f, 0.0f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[28] = UVVertex(glm::vec3(-15.0f, 0.1f, -30.0f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[29] = UVVertex(glm::vec3(15.0f, 0.1f, -30.0f), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	//bottom
	vCube[30] = UVVertex(glm::vec3(-15.0f, -0.1f, 0.0f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[31] = UVVertex(glm::vec3(15.0f, -0.1f, 0.0f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[32] = UVVertex(glm::vec3(15.0f, -0.1f, -30.0f), glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			


	vCube[33] = UVVertex(glm::vec3(-15.0f, -0.1f, 0.0f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[34] = UVVertex(glm::vec3(15.0f, -0.1f, -30.0f),glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[35] = UVVertex(glm::vec3(-15.0f, -0.1f, -30.0f), glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vCube.size() * sizeof(UVVertex), &vCube, GL_STATIC_DRAW);

	CreateTexture(sObj,"ice3.png");
}

void Cube::CreateTexture(GLuint sObj,const char* textureName)
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

	unsigned char* data = stbi_load(textureName, &widthImage, &heightImage, &numberOfChannel,0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	int tLocation_1 = glGetUniformLocation(sObj, "texture1"); 
	glUniform1i (tLocation_1, 0); 
}
void Cube::Update(const GLuint& sObj)
{

	worldTransform = trMatrix * rmMatrix;
	
	unsigned int WT = glGetUniformLocation(sObj, "WorldTransform");

	glUniformMatrix4fv(WT, 1, GL_FALSE, glm::value_ptr(worldTransform));
}	

void Cube::Draw(const GLuint & sObj)
{
	Update(sObj);
	
	int attribPos = glGetAttribLocation(sObj, "vPos");
	int attribNorm = glGetAttribLocation(sObj, "vNormal");
	int attribUV = glGetAttribLocation(sObj, "vUV");

	glEnableVertexAttribArray(attribPos);
	glEnableVertexAttribArray(attribNorm);
	glEnableVertexAttribArray(attribUV);


	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	
	
	glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
	glVertexAttribPointer(attribNorm, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(attribUV, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(attribPos);
	glDisableVertexAttribArray(attribNorm);
	glDisableVertexAttribArray(attribUV);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	

	//glUseProgram(sObj);

	
}
