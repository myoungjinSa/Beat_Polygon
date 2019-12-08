#pragma once

class Timer;
class Camera
{

public:

	glm::vec3 cameraPos{ 0.0f,0.0f,0.0f };
	glm::vec3 cameraTarget{0.0f,0.0f,-1.0f};
	glm::vec3 cameraUp{ 0.0f,1.0f,0.0f };
	glm::vec3 cameraDirection{0.0f,0.0f,-1.0f};


	glm::mat4 rmMatrix = glm::mat4(1.0f);
	glm::mat4 trMatrix = glm::mat4(1.0f);

	glm::mat4 worldTransform = glm::mat4(1.0f);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);


public:

	Camera(glm::vec3 pos,glm::vec3 dir,glm::vec3 up);
	~Camera() {}

	glm::vec3 GetCameraPos() const { return cameraPos; }
	glm::vec3 GetCameraTarget() const { return cameraTarget; }
	void SetPosition(const glm::vec3& pos);
	void Update(const GLuint& sObj,float width,float height);
	void Rotate(Timer t,glm::vec3 axis);

	void MoveLeft(const glm::vec3& pos);
	void MoveRight(const glm::vec3& pos);
	void SetDirection(const glm::vec3& dir);
public:
	bool bRotation = false;
};