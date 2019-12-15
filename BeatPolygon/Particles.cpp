#include "stdafx.h"
#include "Particles.h"


Particle::Particle()
{

}

Particle::~Particle()
{

}

void Particle::Create(GLuint sObj,const glm::vec3& movingDir,glm::vec3 color)
{
	float r = color.r;
	float g = color.g;
	float b = color.b;
	//front
	vCube[0] = Diffuse_Vertex(glm::vec3(-0.1f, 0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[1] = Diffuse_Vertex(glm::vec3(-0.1f, -0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[2] = Diffuse_Vertex(glm::vec3(0.1f, 0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			


	vCube[3] = Diffuse_Vertex(glm::vec3(0.1f, 0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[4] = Diffuse_Vertex(glm::vec3(-0.1f, -0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[5] = Diffuse_Vertex(glm::vec3(0.1f, -0.1f, -0.1f), glm::vec4(r,g,b,1.0f));			

	//left
	vCube[6] = Diffuse_Vertex(glm::vec3(-0.1f, 0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[7] = Diffuse_Vertex(glm::vec3(-0.1f, 0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[8] = Diffuse_Vertex(glm::vec3(-0.1f, -0.1f, 0.1f), glm::vec4(r,g,b,1.0f));			


	vCube[9] = Diffuse_Vertex(glm::vec3(-0.1f, 0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[10] = Diffuse_Vertex(glm::vec3(-0.1f, -0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[11] = Diffuse_Vertex(glm::vec3(-0.1f, -0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			

	//back
	vCube[12] = Diffuse_Vertex(glm::vec3(-0.1f, 0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[13] = Diffuse_Vertex(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[14] = Diffuse_Vertex(glm::vec3(-0.1f, -0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			


	vCube[15] = Diffuse_Vertex(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[16] = Diffuse_Vertex(glm::vec3(0.1f, -0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[17] = Diffuse_Vertex(glm::vec3(-0.1f, -0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			

	//right
	vCube[18] = Diffuse_Vertex(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[19] = Diffuse_Vertex(glm::vec3(0.1f, 0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[20] = Diffuse_Vertex(glm::vec3(0.1f, -0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			


	vCube[21] = Diffuse_Vertex(glm::vec3(0.1f, 0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[22] = Diffuse_Vertex(glm::vec3(0.1f, -0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[23] = Diffuse_Vertex(glm::vec3(0.1f, -0.1f, 0.0f), glm::vec4(r,g,b,1.0f));			

	//top
	vCube[24] = Diffuse_Vertex(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[25] = Diffuse_Vertex(glm::vec3(-0.1f, 0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[26] = Diffuse_Vertex(glm::vec3(-0.1f, 0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			


	vCube[27] = Diffuse_Vertex(glm::vec3(0.1f, 0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[28] = Diffuse_Vertex(glm::vec3(-0.1f, 0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[29] = Diffuse_Vertex(glm::vec3(0.1f, 0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			

	//bottom
	vCube[30] = Diffuse_Vertex(glm::vec3(-0.1f, -0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[31] = Diffuse_Vertex(glm::vec3(0.1f, -0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[32] = Diffuse_Vertex(glm::vec3(0.1f, -0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			


	vCube[33] = Diffuse_Vertex(glm::vec3(-0.1f, -0.1f, 0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[34] = Diffuse_Vertex(glm::vec3(0.1f, -0.1f, -0.1f),glm::vec4(r,g,b,1.0f));			
	vCube[35] = Diffuse_Vertex(glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec4(r,g,b,1.0f));			

	
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vCube.size() * sizeof(Diffuse_Vertex), &vCube, GL_STATIC_DRAW);



	movingDirection = glm::vec3(movingDir.x, movingDir.y, movingDir.z);
	fSpeed = 20.0f;
	maxExplosionDuration = 5.0f;


}

void Particle::UpdatePos(const float& elapsedTime,const GLuint& sObj)
{
	explosionTime += elapsedTime;
	if (explosionTime <= maxExplosionDuration)
	{
		glm::vec3 pos = position;
		//std::cout << movingDirection.x << "," << movingDirection.y << "," << movingDirection.z << "\n";
		position.x =  pos.x + (movingDirection.x * fSpeed * elapsedTime);
		position.y = pos.y + (movingDirection.y * fSpeed * elapsedTime);
		position.z = pos.z + (movingDirection.z * fSpeed * elapsedTime);

		trMatrix[3].x = position.x;
		trMatrix[3].y = position.y;
		trMatrix[3].z = position.z;


		worldTransform = trMatrix * rmMatrix;

		unsigned int WT = glGetUniformLocation(sObj, "WorldTransform");

		glUniformMatrix4fv(WT, 1, GL_FALSE, glm::value_ptr(worldTransform));
	}
	
}

void Particle::Draw(const float& elapsedTime,const GLuint& sObj)
{
	UpdatePos(elapsedTime,sObj);
	
	int attribPos = glGetAttribLocation(sObj, "vPos");
	int attribCol = glGetAttribLocation(sObj, "vColor");

	glEnableVertexAttribArray(attribPos);
	glEnableVertexAttribArray(attribCol);


	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	
	
	glVertexAttribPointer(attribPos, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
	glVertexAttribPointer(attribCol, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

	

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(attribPos);
	glDisableVertexAttribArray(attribCol);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}

void Particle::SetPosition(const glm::vec3 & pos)
{
	position = pos;
	trMatrix[3].x = pos.x;
	trMatrix[3].y = pos.y;
	trMatrix[3].z = pos.z;
}

glm::vec3 Particle::GetPosition()
{
	return position;
}

void Particle::InitShader(GLuint shaderObj)
{
	shaderObject = shaderObj;
}