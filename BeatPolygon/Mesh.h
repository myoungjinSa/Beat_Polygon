#pragma once

class Mesh
{

public:

	
	virtual void Update(const GLuint &sObj) = 0;
	virtual void Draw(const GLuint & sObj) = 0;
	virtual void Draw(const float& elapsedTime, const GLuint& sObj) = 0;
	//virtual void Draw(const float& elapsedTime, const GLuint & sObj, const glm::vec3& position) = 0;
};