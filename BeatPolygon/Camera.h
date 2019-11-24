#pragma once

class Camera
{

private:

	glm::vec3 cameraPos{ 0.0f,0.0f,0.0f };
	glm::vec3 cameraDirection{0.0f,0.0f,-1.0f};
	glm::vec3 cameraUp{ 0.0f,1.0f,0.0f };


public:

	Camera(glm::vec3 pos,glm::vec3 dir,glm::vec3 up);
	~Camera() {}

	glm::vec3 GetCameraPos() const { return cameraPos; }
	void SetPosition(const glm::vec3& pos);
	void Update(const GLuint& sObj,float width,float height);
};