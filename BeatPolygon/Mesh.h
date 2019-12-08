#pragma once

class Mesh
{

public:

	
	virtual void Update(const GLuint &sObj) = 0;
	virtual void Draw(const GLuint & sObj) = 0;

};