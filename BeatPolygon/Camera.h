#pragma once

class Timer;
class Camera
{

private:

	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;
	glm::vec3 cameraDirection;


	glm::mat4 rmMatrix;
	glm::mat4 trMatrix;

	glm::mat4 worldTransform;

	glm::mat4 view;
	glm::mat4 projection ;

public:
	Camera()=delete;
	Camera(const glm::vec3& pos,const glm::vec3& dir,const glm::vec3& up);
	~Camera();

	Camera(const Camera& ref)=delete;
	const Camera& operator=(const Camera& ref)=delete;

	Camera(Camera&& rval) = delete;
	Camera& operator=(Camera&& rval) = delete;


	glm::vec3 GetCameraPos() const { return cameraPos; }
	glm::vec3 GetCameraTarget() const { return cameraTarget; }
	void SetPosition(const glm::vec3& pos);
	void Update(const GLuint& sObj,const float& width,const float& height);
	void Rotate(const Timer& t,const glm::vec3& axis);

	void MoveLeft(const glm::vec3& pos);
	void MoveRight(const glm::vec3& pos);
	void SetDirection(const glm::vec3& dir);

};