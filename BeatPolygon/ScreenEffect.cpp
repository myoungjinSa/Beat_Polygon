#include "stb_image.h"
#include "stdafx.h"

#include "ScreenEffect.h"

ScreenEffect::ScreenEffect()
	:trMatrix{glm::mat4(1.0f)},
	rmMatrix{glm::mat4(1.0f)},
	scMatrix{glm::mat4(1.0f)},
	worldTransform{glm::mat4(1.0f)},
	position{glm::vec3(0.0f,0.0f,0.0f)}
{

}

ScreenEffect::~ScreenEffect()
{

}


void ScreenEffect::Create(const GLuint& sObj,const char* image,const char* image2)
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
	CreateTexture(sObj,image,image2);

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
	
	if (isGameStart)
	{

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
	}
	else
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
	}

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPos);
	glDisableVertexAttribArray(attribCol);
	glDisableVertexAttribArray(attribUV);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void ScreenEffect::IsGameStart(const bool& isStart)
{
	isGameStart = isStart;
}
void ScreenEffect::CreateTexture(const GLuint& sObj,const char* texture1,const char* texture2)
{
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT,16.0f);

	
	stbi_set_flip_vertically_on_load(true); 
	int widthImage, heightImage, numberOfChannel;

	unsigned char** data = new unsigned char*[2];

	if (data) {
		for (int i = 0 ; i<2 ;++i)
		{
			data[i] = new unsigned char;
		}
	}

	//텍스쳐 이름 생성
	glGenTextures(1, &texture[0]);
	
	//이제 GL_TEXTURE_2D 바인딩 포인트를 사용하여 콘텍스트에 바인딩 한다.
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data[0] = stbi_load(texture1, &widthImage, &heightImage, &numberOfChannel,0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, data[0]);


	glGenTextures(2, &texture[1]);
		//이제 GL_TEXTURE_2D 바인딩 포인트를 사용하여 콘텍스트에 바인딩 한다.
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	data[1] = stbi_load(texture2, &widthImage, &heightImage, &numberOfChannel,0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, data[1]);


	int tLocation_1 = glGetUniformLocation(sObj, "sampler"); 
	glUniform1i (tLocation_1, 0); 
}