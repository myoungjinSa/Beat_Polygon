#include "stdafx.h"
#include "Camera.h"

Camera::Camera(glm::vec3 pos,glm::vec3 dir,glm::vec3 up)
	: cameraPos{pos},cameraDirection{dir},cameraUp{up}
{
	
}

void Camera::Update(const GLuint& sObj,float width,float height)
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(sObj, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), width / height, 0.1f, 100.0f);
	//projection = glm::ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	unsigned int projectionLocation = glGetUniformLocation(sObj, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}

void Camera::SetPosition(const glm::vec3& pos)
{
	cameraPos = pos;
}
