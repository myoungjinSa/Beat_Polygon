#include "stb_image.h"
#include "stdafx.h"

#include "ScreenEffect.h"

ScreenEffect::ScreenEffect()
{

}

ScreenEffect::~ScreenEffect()
{

}


void ScreenEffect::Create(const GLuint& sObj)
{
	aSquare[0] = UVAlphaVertex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	aSquare[1] = UVAlphaVertex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	aSquare[2] = UVAlphaVertex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));

	aSquare[3] = UVAlphaVertex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
	aSquare[4] = UVAlphaVertex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	aSquare[5] = UVAlphaVertex(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f));

	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, aSquare.size() * sizeof(UVAlphaVertex), &aSquare, GL_STATIC_DRAW);

	shaderObject = sObj;
	CreateTexture(sObj,"iceScreen.png");
}

void ScreenEffect::Update(const GLuint& sObj)
{
}

void ScreenEffect::Draw(const GLuint& sObj)
{
	Update(sObj);

	int attribPos = glGetAttribLocation(sObj, "vPos");
	int attribCol = glGetAttribLocation(sObj, "vColor");
	int attribUV = glGetAttribLocation(sObj, "vTexcoord");

	glEnableVertexAttribArray(attribPos);
	glEnableVertexAttribArray(attribCol);
	glEnableVertexAttribArray(attribUV);


	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	
	
	glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), nullptr);
	glVertexAttribPointer(attribCol, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(attribUV, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPos);
	glDisableVertexAttribArray(attribCol);
	glDisableVertexAttribArray(attribUV);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ScreenEffect::CreateTexture(GLuint sObj,const char* textureName)
{
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT,16.0f);

	
	stbi_set_flip_vertically_on_load(true); 
	int widthImage, heightImage, numberOfChannel;

	

	//�ؽ��� �̸� ����
	glGenTextures(1, &texture);
	
	//���� GL_TEXTURE_2D ���ε� ����Ʈ�� ����Ͽ� ���ؽ�Ʈ�� ���ε� �Ѵ�.
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(textureName, &widthImage, &heightImage, &numberOfChannel,0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	int tLocation_1 = glGetUniformLocation(sObj, "sampler"); 
	glUniform1i (tLocation_1, 0); 
}