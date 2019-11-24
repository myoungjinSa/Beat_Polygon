#pragma once
#pragma comment(lib,"freeglut.lib")
#pragma comment(lib, "glew32.lib")
#include <gl/glew.h>

#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm\ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <iterator>
#include <fstream>

class Vertex
{
public:
	float fx;
	float fy;
	float fz;
	float r;
	float g;
	float b;
public:
	Vertex() = default;
	Vertex(glm::vec3 vec,glm::vec3 color) :fx{ vec.x }, fy{ vec.y }, fz{ vec.z }, r{ color.x }, g{ color.y }, b{color.z} {};

};



