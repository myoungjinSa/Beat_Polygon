#include "stdafx.h"
#include "Camera.h"
#include "Timer.h"


Camera::Camera(const glm::vec3& pos,const glm::vec3& dir,const glm::vec3& up)
	: cameraPos{ pos }, 
	cameraTarget{ dir }, 
	cameraUp{ up },
	cameraDirection{0.0f,0.0f,-1.0f},
	rmMatrix{ glm::mat4(1.0f) },
	trMatrix{ glm::mat4(1.0f) },
	worldTransform{ glm::mat4(1.0f) },
	view{ glm::mat4(1.0f) },
	projection {glm::mat4(1.0f)}

{
	
	
}

void Camera::Update(const GLuint& sObj,const float& width,const float& height)
{

	view = glm::lookAt(cameraPos, cameraTarget, cameraUp) * rmMatrix;
	unsigned int viewLocation = glGetUniformLocation(sObj, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	

	projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
	//projection = glm::ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	unsigned int projectionLocation = glGetUniformLocation(sObj, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


}

void Camera::SetPosition(const glm::vec3& pos)
{
	cameraPos = pos;
	
	trMatrix[3].x = cameraPos.x;
	trMatrix[3].y = cameraPos.y;
	trMatrix[3].z = cameraPos.z;

}
void Camera::MoveLeft(const glm::vec3& pos)
{
	SetPosition(pos);
	cameraTarget.x = pos.x;
}

void Camera::MoveRight(const glm::vec3& pos)
{
	SetPosition(pos);
	cameraTarget.x = pos.x;
}

void Camera::SetDirection(const glm::vec3& center)
{
	cameraTarget = center;
	glm::vec3 dir = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up = glm::normalize(glm::cross(cameraUp, dir));
}

void Camera::Rotate(const Timer& t,const glm::vec3& axis)
{

	const float rotationSpeed = 100.0f;

	
	rmMatrix = glm::rotate(rmMatrix, glm::radians(t.GetTimeElapsed() * rotationSpeed),axis );

	
}
