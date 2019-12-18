#pragma once
#include "Mesh.h"

class Camera;


class Light :public Mesh
{
public:
	Light() = delete;
	Light(const Diffuse_Vertex& v0,const Diffuse_Vertex& v1,const Diffuse_Vertex& v2,const Diffuse_Vertex& v3,
		const Diffuse_Vertex& v4,const Diffuse_Vertex& v5, const Diffuse_Vertex& v6,const Diffuse_Vertex& v7);
	virtual ~Light();

	void Update(const GLuint& sObj)final;
	void Draw(const GLuint& sObj)final;
	void Draw(const float& elapsedTime, const GLuint& sObj) {}
//	void Draw(const float& elapsedTime, const GLuint & sObj, const glm::vec3& position) {  }
	void SetRange(const float& range);
	void SetPosition(const glm::vec3& pos);
	void SetSpeed(const float& speed);
	void SetWidth(const float& w);
	void SetHeight(const float& h);
	void SetDepth(const float& d);

	const float& GetDepth() const;
	const float& GetWidth() const;
	const float& GetHeight() const;
	const float& GetSpeed() const;

	const glm::vec3& GetPosition() const { return position; }
	void InitShader(const GLuint& n);


public:
	enum class DIRECTION{ LEFT,RIGHT,STOP }dir;
	const int vCount = 8;
	const int indexCount = 36;
	const float rotationSpeed = 20.0f;

	
	GLuint vertexBufferObject;
	GLuint elementBufferObject;

	Diffuse_Vertex v0; Diffuse_Vertex v1; Diffuse_Vertex v2; 
	Diffuse_Vertex v3; Diffuse_Vertex v4; Diffuse_Vertex v5; 
	Diffuse_Vertex v6; Diffuse_Vertex v7;

	unsigned int Indices[36];

	bool bDash;

	glm::vec3 position ;

private:

	glm::mat4 trMatrix;
	glm::mat4 rmMatrix;
	glm::mat4 scMatrix;

	glm::mat4 worldTransform;


	GLuint shaderObject;

private:
	
	float width, height,depth;
	float fSpeed;
	float fRange;
	
};
