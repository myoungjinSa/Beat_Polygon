#pragma once
#include "Mesh.h"

class ScreenEffect : public Mesh
{
public:
	explicit ScreenEffect();
	virtual ~ScreenEffect();

	ScreenEffect(const ScreenEffect& ref) = delete;
	ScreenEffect& operator=(const ScreenEffect& ref) = delete;

	ScreenEffect(ScreenEffect&& rval) = delete;
	ScreenEffect& operator=(ScreenEffect&& rval) = delete;
	
	void Create(const GLuint& sObj,const char* image,const char* image2);
	void Update(const GLuint& sObj)final;

	void Draw(const GLuint& sObj)final;
	
	void CreateTexture(const GLuint& sObj,const char* texture1,const char* texture2);
	void IsGameStart(const bool& texture);


private:
	glm::mat4 trMatrix;
	glm::mat4 rmMatrix;
	glm::mat4 scMatrix;

	glm::mat4 worldTransform;

	glm::vec3 position;

	

	GLuint sampler;
	GLuint texture[2];
	GLuint shaderObject;
	GLuint vertexBufferObject;

	bool isGameStart;

	const int vCount;

	
	std::array<UVAlphaVertex, 6> aSquare;
};