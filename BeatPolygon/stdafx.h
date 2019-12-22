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
//#include <iosfwd>
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
	explicit Diffuse_Vertex(const glm::vec3& vec, const glm::vec4& color) :fx{ vec.x }, fy{ vec.y }, fz{ vec.z }, r{ color.x }, g{ color.y }, b{ color.z }, a{ color.a }{};
	~Diffuse_Vertex() = default;
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
	explicit Normal_Vertex(const glm::vec3& vec, const glm::vec4& color, const glm::vec3& normal) :fx{ vec.x }, fy{ vec.y }, fz{ vec.z }, r{ color.x }, g{ color.y }, b{ color.z }, a{ color.a }, nx{normal.x},ny{normal.y},nz{normal.z} {};
	~Normal_Vertex() = default;
};

class UVAlphaVertex
{
public:
	float fx;
	float fy;
	float fz;
	float r;
	float g;
	float b;
	float a;
	float fu;
	float fv;

public:
	UVAlphaVertex() = default;
	explicit UVAlphaVertex(const glm::vec3& vec,const glm::vec4& color,const glm::vec2& uv )
		: fx{vec.x},fy{vec.y},fz{vec.z},r{color.r},g{color.g},b{color.b},a{color.a},fu{uv.x},fv{uv.y}
	{}
	~UVAlphaVertex() = default;
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
	explicit UVVertex(const glm::vec3& vec,const glm::vec3& normal, const glm::vec2& uv) :fx{ vec.x }, fy{ vec.y }, fz{ vec.z }, nx{ normal.x }, ny{ normal.y }, nz{ normal.z }, fu{ uv.x }, fv{ uv.y } {};
	~UVVertex() = default;
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
	explicit UVColorVertex(const glm::vec3& vec,const glm::vec4& col,const glm::vec3& normal,const glm::vec2& uv) 
		:fx{ vec.x }, fy{ vec.y }, fz{ vec.z }, fr{ col.r }, fg{ col.g }, fb{ col.b }, fa{ col.a }, nx{ normal.x }, ny{ normal.y }, nz{ normal.z }, fu{ uv.x }, fv{ uv.y } {};
	~UVColorVertex() = default;
};








