#include "stdafx.h"
#include "Camera.h"
#include "Timer.h"

Camera::Camera(glm::vec3 pos,glm::vec3 dir,glm::vec3 up)
	: cameraPos{pos},cameraTarget{dir},cameraUp{up}
{
	
	
}

void Camera::Update(const GLuint& sObj,float width,float height)
{

	view = glm::lookAt(cameraPos, cameraTarget, cameraUp) * rmMatrix;
	unsigned int viewLocation = glGetUniformLocation(sObj, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	

	projection = glm::perspective(glm::radians(90.0f), width / height, 5.0f, 100.0f);
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

void Camera::Rotate(Timer t,glm::vec3 axis)
{

	const float rotationSpeed = 100.0f;

	
	rmMatrix = glm::rotate(rmMatrix, glm::radians(t.GetTimeElapsed() * rotationSpeed),axis );

	
}
