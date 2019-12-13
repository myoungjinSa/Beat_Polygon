#include "stb_image.h"

#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
	:width{0.0f},height{0.0f}
{

}

Wall::~Wall()
{
	
}


void Wall::SetWidth(float w)
{
	width = w;
}

void Wall::SetHeight(float h)
{
	height = h;
}

void Wall::SetDepth(float d)
{
	depth = d;
}
float Wall::Random(float min,float max)
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	//default_random_engine dre;
	std::uniform_real_distribution<double> urd(min, max);

	return (float)urd(dre);
	
}
float Wall::Random()
{
	return(rand() / float(RAND_MAX));
}



void Wall::InitParticleShader(const GLuint& shader)
{
	particleShaderObject = shader;
}
void Wall::CreateParticles()
{
	for(int i =0;i<particleCount;++i)
	{
		aParticles[i].Create(particleShaderObject,glm::vec3(Random(-1.0f,1.0f),Random(-1.0f,1.0f),Random(-1.0f,1.0f)));
	}
}

void Wall::SaveExplosionPos(const glm::vec3& pos)
{
	std::cout << pos.x << "," << pos.y << "," << pos.z << std::endl;
	for(int i =0;i<particleCount;++i)
	{
		aParticles[i].SetPosition(pos);
	}
}
void Wall::Create(const GLuint& sObj,float width, float height,float depth)
{
		
	this->width = width;
	this->height = height;
	this->depth = depth;

	halfWidth = width * 0.5f;
	halfHeight = height * 0.5f;
	halfDepth = depth * 0.5f;


	//front
	vCube[0] = UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f + halfHeight, 0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[1] = UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f - halfHeight, 0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[2] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f + halfHeight, 0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			


	vCube[3] =  UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f + halfHeight, 0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[4] =  UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f - halfHeight, 0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[5] =  UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f - halfHeight, 0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	//left
	vCube[6] =  UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f + halfHeight, 0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[7] =  UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f + halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(-1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[8] =  UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f - halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			


	vCube[9] =  UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f + halfHeight,0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[10] = UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f - halfHeight,0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[11] = UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f - halfHeight,0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	//back
	vCube[12] = UVColorVertex(glm::vec3(0.0f- halfWidth,0.0f + halfHeight, 0.0f- halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(-1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[13] = UVColorVertex(glm::vec3(0.0f + halfWidth,0.0f + halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[14] = UVColorVertex(glm::vec3(0.0f- halfWidth,0.0f - halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			


	vCube[15] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f + halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[16] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f - halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[17] = UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f - halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			

	//right
	vCube[18] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f + halfHeight,0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[19] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f + halfHeight,0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[20] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f - halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			


	vCube[21] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f+ halfHeight,0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[22] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f - halfHeight,0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[23] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f - halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			

	//top
	vCube[24] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f + halfHeight,  0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[25] = UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f + halfHeight,  0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(-1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[26] = UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f + halfHeight,  0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(0.0f, 0.0f));			


	vCube[27] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f + halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[28] = UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f + halfHeight, 0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[29] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f + halfHeight, 0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	//bottom
	vCube[30] = UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f - halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[31] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f - halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[32] = UVColorVertex(glm::vec3(0.0f + halfWidth, 0.0f - halfHeight, 0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			


	vCube[33] = UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f- halfHeight, 0.0f - halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[34] = UVColorVertex(glm::vec3(0.0f + halfWidth,0.0f  - halfHeight, 0.0f+ halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f),glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[35] = UVColorVertex(glm::vec3(0.0f - halfWidth, 0.0f - halfHeight,0.0f + halfDepth),glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vCube.size() * sizeof(UVColorVertex), &vCube, GL_STATIC_DRAW);

	SetSpeed(30.0f);
	
	shaderObject = sObj;


	CreateParticles();
	CreateTexture(sObj);

}

void Wall::SetPosition(const glm::vec3& pos)
{
	position = pos;
	trMatrix[3].x = pos.x;
	trMatrix[3].y = pos.y;
	trMatrix[3].z = pos.z;

	

}

void Wall::SetSpeed(float speed)
{
	fSpeed = speed;
}
void Wall::Move(float time)
{

	position.z += fSpeed * time;

	SetPosition(position);
}

void Wall::CreateTexture(const GLuint& sObj)
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
void Wall::Update(const GLuint& sObj)
{

	if(b_Blowing)
	{
		
	}
	else
	{
		worldTransform = trMatrix * rmMatrix;

		unsigned int WT = glGetUniformLocation(sObj, "WorldTransform");

		glUniformMatrix4fv(WT, 1, GL_FALSE, glm::value_ptr(worldTransform));
	}
}

void Wall::Draw(const float& elapsedTime,const GLuint& sObj)
{
	if(b_Blowing)
	{
		glUseProgram(particleShaderObject);

		for(int i = 0;i<particleCount;++i)
		{
			aParticles[i].Draw(elapsedTime,sObj);
		}

	}
	else
	{
		if (b_Active)
		{
			glUseProgram(shaderObject);
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

			glDrawArrays(GL_TRIANGLES, 0, 36);


			glDisableVertexAttribArray(attribPos);
			glDisableVertexAttribArray(attribCol);
			glDisableVertexAttribArray(attribNorm);
			glDisableVertexAttribArray(attribUV);


			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

}