#pragma once

#pragma comment(lib,"freeglut.lib")
#pragma comment(lib, "glew32.lib")
#define STB_IMAGE_IMPLEMENTATION
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
#include <array>
#include <map>
#include <random>


//#define WRITE_MUSIC
	// 키입력 정의
enum KEY_TYPE
{
	NONE				= 0x0000,
	UP					= 0x0001,
	DOWN				= 0x0002,
	RIGHT				= 0x0004,
	LEFT					= 0x0008,

	UP_RIGHT			= 0x0005,
	UP_LEFT			= 0x0009,
	DOWN_RIGHT	= 0x0006,
	DOWN_LEFT		= 0x000A
};
class Diffuse_Vertex
{
public:
	float fx;
	float fy;
	float fz;
	float r;
	float g;
	float b;
	float a;
	
public:
	Diffuse_Vertex() = default;
	Diffuse_Vertex(glm::vec3 vec, glm::vec4 color) :fx{ vec.x }, fy{ vec.y }, fz{ vec.z }, r{ color.x }, g{ color.y }, b{ color.z }, a{ color.a }{};

};

class Normal_Vertex
{
public:
	float fx;
	float fy;
	float fz;
	float r;
	float g;
	float b;
	float a;
	float nx;
	float ny;
	float nz;
public:
	Normal_Vertex() = default;
	Normal_Vertex(glm::vec3 vec, glm::vec4 color, glm::vec3 normal) :fx{ vec.x }, fy{ vec.y }, fz{ vec.z }, r{ color.x }, g{ color.y }, b{ color.z }, a{ color.a }, nx{normal.x},ny{normal.y},nz{normal.z} {};

};


class UVVertex
{
public:
	float fx;
	float fy;
	float fz;
	float nx;
	float ny;
	float nz;
	float fu;
	float fv;
public:
	UVVertex() = default;
	UVVertex(glm::vec3 vec, glm::vec3 normal, glm::vec2 uv) :fx{ vec.x }, fy{ vec.y }, fz{ vec.z }, nx{ normal.x }, ny{ normal.y }, nz{ normal.z }, fu{ uv.x }, fv{ uv.y } {};

};

class UVColorVertex
{
public:
	float fx;
	float fy;
	float fz;
	float fr;
	float fg;
	float fb;
	float fa;
	float nx;
	float ny;
	float nz;
	float fu;
	float fv;
public:
	UVColorVertex() = default;
	UVColorVertex(glm::vec3 vec, glm::vec4 col, glm::vec3 normal, glm::vec2 uv) 
		:fx{ vec.x }, fy{ vec.y }, fz{ vec.z }, fr{ col.r }, fg{ col.g }, fb{ col.b }, fa{ col.a }, nx{ normal.x }, ny{ normal.y }, nz{ normal.z }, fu{ uv.x }, fv{ uv.y } {};

};








