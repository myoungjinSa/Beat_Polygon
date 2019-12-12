#pragma once
#include "Mesh.h"

class Camera;
class Light :public Mesh
{
public:
	Light() = default;
	Light(Diffuse_Vertex v0, Diffuse_Vertex v1, Diffuse_Vertex v2, Diffuse_Vertex v3, Diffuse_Vertex v4, Diffuse_Vertex v5, Diffuse_Vertex v6, Diffuse_Vertex v7);
	virtual ~Light();

	void Update(const GLuint& sObj)final;
	void Draw(const GLuint& sObj)final;
	void Draw(const float& elapsedTime, const GLuint& sObj) {}
//	void Draw(const float& elapsedTime, const GLuint & sObj, const glm::vec3& position) {  }
	void SetRange(float range);
	void SetPosition(const glm::vec3& pos);
	void SetSpeed(float speed);
	void SetWidth(float w);
	void SetHeight(float h);
	void SetDepth(float d);

	float GetDepth() { return depth; }
	float GetWidth() { return width; }
	float GetHeight() { return height; }
	float GetSpeed() { return fSpeed; }


	glm::vec3 GetPosition() { return position; }
	void InitShader(GLuint n);


	glm::mat4 trMatrix = glm::mat4(1.0f);
	glm::mat4 rmMatrix = glm::mat4(1.0f);
	glm::mat4 scMatrix = glm::mat4(1.0f);

	glm::mat4 worldTransform = glm::mat4(1.0f);

	glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);


	Diffuse_Vertex v0; Diffuse_Vertex v1; Diffuse_Vertex v2; 
	Diffuse_Vertex v3; Diffuse_Vertex v4; Diffuse_Vertex v5; 
	Diffuse_Vertex v6; Diffuse_Vertex v7;


	GLuint shaderObject;
	GLuint vertexBufferObject;
	GLuint elementBufferObject;
	bool bDash{ false };

	unsigned int Indices[36];

	const int vCount = 8;
	const int indexCount = 36;

	enum class DIRECTION{ LEFT,RIGHT,STOP }dir;
	

private:
	
	float width, height,depth;
	float fSpeed;
	float fRange{ 0.0f };
	glm::mat4 rm = glm::mat4(1.0f);
	glm::vec3 look = glm::vec3(0.0f, 0.0f, 0.0f);
	float rotationSpeed = 20.0f;
};
