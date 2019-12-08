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

	void SetRange(float range);
	void Rotate(Camera *pCamera,float fTimeElapsed);
	void SetPosition(const glm::vec3& pos);
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

	unsigned int Indices[36];

	const int vCount = 8;
	const int indexCount = 36;

	enum class DIRECTION{ LEFT,RIGHT,STOP }dir;


	bool bLightOn{ true };
private:

	float fRange{ 0.0f };
	glm::mat4 rm = glm::mat4(1.0f);
	glm::vec3 look = glm::vec3(0.0f, 0.0f, 0.0f);
	float rotationSpeed = 20.0f;
};