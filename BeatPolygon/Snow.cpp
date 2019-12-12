#include "stdafx.h"
#include "Snow.h"



void Snow::SetPosition(const glm::vec3& pos)
{
	trMatrix[3].x = pos.x;
	trMatrix[3].y = pos.y;
	trMatrix[3].z = pos.z;


}

void Snow::Create()
{
		//front
	vCube[0] = UVVertex(glm::vec3(-0.05f, 0.05f, 0.05f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[1] = UVVertex(glm::vec3(-0.05f, 0.0f, 0.05f),glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[2] = UVVertex(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			


	vCube[3] = UVVertex(glm::vec3(0.05f, 0.05f, 0.05f),glm::vec3(1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[4] = UVVertex(glm::vec3(-0.05f, 0.0f, 0.05f),glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[5] = UVVertex(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	//left
	vCube[6] = UVVertex(glm::vec3(-0.05f, 0.05f, 0.05f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[7] = UVVertex(glm::vec3(-0.05f, 0.05f, -0.05f),glm::vec3(-1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[8] = UVVertex(glm::vec3(-0.05f, 0.0f, -0.05f), glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			


	vCube[9] = UVVertex(glm::vec3(-0.05f, 0.05f, 0.05f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[10] = UVVertex(glm::vec3(-0.05f, 0.0f, -0.05f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[11] = UVVertex(glm::vec3(-0.05f, 0.0f, 0.05f), glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	//back
	vCube[12] = UVVertex(glm::vec3(-0.05f, 0.05f, -0.05f),glm::vec3(-1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[13] = UVVertex(glm::vec3(0.05f, 0.05f, -0.05f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[14] = UVVertex(glm::vec3(-0.05f, 0.0f, -0.05f), glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			


	vCube[15] = UVVertex(glm::vec3(0.05f, 0.05f, -0.05f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[16] = UVVertex(glm::vec3(0.05f, 0.0f, -0.05f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[17] = UVVertex(glm::vec3(-0.05f, 0.0f, -0.05f), glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			

	//right
	vCube[18] = UVVertex(glm::vec3(0.05f, 0.05f, -0.05f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[19] = UVVertex(glm::vec3(0.05f, 0.05f, 0.05f),glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[20] = UVVertex(glm::vec3(0.05f, 0.0f, -0.05f), glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			


	vCube[21] = UVVertex(glm::vec3(0.05f, 0.05f, 0.05f),glm::vec3(1.0f,1.0f,1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[22] = UVVertex(glm::vec3(0.05f, 0.0f, 0.05f),glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[23] = UVVertex(glm::vec3(0.05f, 0.0f, -0.05f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 0.0f));			

	//top
	vCube[24] = UVVertex(glm::vec3(0.05f, 0.05f, -0.05f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[25] = UVVertex(glm::vec3(-0.05f, 0.05f, -0.05f),glm::vec3(-1.0f,1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[26] = UVVertex(glm::vec3(-0.05f, 0.05f, 0.05f), glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(0.0f, 0.0f));			


	vCube[27] = UVVertex(glm::vec3(0.05f, 0.05f, -0.05f),glm::vec3(1.0f,1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[28] = UVVertex(glm::vec3(-0.05f, 0.05f, 0.05f),glm::vec3(-1.0f,1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[29] = UVVertex(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(1.0f,1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	//bottom
	vCube[30] = UVVertex(glm::vec3(-0.05f, 0.0f, -0.05f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(1.0f, 1.0f));			
	vCube[31] = UVVertex(glm::vec3(0.05f, 0.0f, -0.05f),glm::vec3(1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[32] = UVVertex(glm::vec3(0.05f, 0.0f, 0.05f), glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			


	vCube[33] = UVVertex(glm::vec3(-0.05f, 0.0f, -0.05f),glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec2(0.0f, 1.0f));			
	vCube[34] = UVVertex(glm::vec3(0.05f, 0.0f, 0.05f),glm::vec3(1.0f,-1.0f,1.0f), glm::vec2(0.0f, 0.0f));			
	vCube[35] = UVVertex(glm::vec3(-0.05f, 0.0f, 0.05f), glm::vec3(-1.0f,-1.0f,1.0f), glm::vec2(1.0f, 0.0f));			

	
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UVVertex) * 36, &vCube, GL_STATIC_DRAW);


}
void Snow::MoveDown(float timeElapsed)
{
	

	trMatrix[3].y -=  fSpeed * timeElapsed;
	if(trMatrix[3].y <= 0.0f)
	{
	
		trMatrix[3].y = 30.0f;
		
	}
}
void Snow::SetSpeed(float speed)
{
	this->fSpeed = speed;
}
void Snow::Update(const GLuint& sObj)
{

	
	glm::mat4 worldTransform = trMatrix * rmMatrix;

	unsigned int WT = glGetUniformLocation(sObj, "WorldTransform");

	glUniformMatrix4fv(WT, 1, GL_FALSE, glm::value_ptr(worldTransform));
}

void Snow::Draw(const GLuint& sObj)
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
	

	

	
	glDrawArrays(GL_TRIANGLES, 0,36);


	glDisableVertexAttribArray(attribPos);
	glDisableVertexAttribArray(attribNorm);
	glDisableVertexAttribArray(attribUV);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}