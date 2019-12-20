#pragma once
#include "Mesh.h"

class Cube : public Mesh
{
private:
	GLuint sampler;
	GLuint texture;
	GLuint shaderObject;
	
	glm::mat4 trMatrix;
	glm::mat4 rmMatrix;
	glm::mat4 scMatrix;
	glm::mat4 worldTransform;

public:

	GLuint vertexBufferObject;
	
	const int vertexCount;
	std::array<UVVertex, 36> vCube;


	
public:

	explicit Cube();
	virtual ~Cube();

	Cube(const Cube& ref) = delete;
	const Cube& operator=(const Cube& ref) = delete;

	Cube(Cube&& rVal) = delete;
	Cube& operator=(Cube&& rVal) = delete;
	
	void CreateTexture(const GLuint& sObj,const char* textureName);
	void Create(const GLuint& sObj);
	
	void Update(const GLuint &sObj);
	void Draw(const GLuint & sObj);
	void Draw(const float& elapsedTime, const GLuint& sObj) {}
	
	void SetPosition(const glm::vec3 & pos);

	const glm::vec3& GetPosition() const;

};