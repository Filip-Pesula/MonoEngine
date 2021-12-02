#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include <Test.h>
#include <concepts>
#ifdef Debug
#include <iostream>

#define Log(x) std::cout<<"\x1B[37m" <<x << "\x1B[0m"<<std::endl
#define LogWarn(x) std::cout<<"\x1B[33m" << x << "\x1B[0m" <<std::endl
#define LogError(x) std::cout<<"\x1B[31m" << x << "\x1B[0m" <<std::endl

#else
#define Log(x)
#endif

#if defined(Debug) && defined(_DEBUG_ALLOC)
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//allocations to be of _CLIENT_BLOCK type
#else
#define MYDEBUG_NEW
#endif // _DEBUG

#ifdef _DEBUG
//#define new MYDEBUG_NEW
#endif
#endif //Debug


#include "Vecf.h"
#include <math.h> 
#include <MonoStd/monoConcepts.h>
#include "Unit.h"
#include "Vec2.h"
#include "Vec3.h"




struct Vec2i
{
	int x;
	int y;
	Vec2i():
		x(0),
		y(0)
	{
	}
	Vec2i(int x, int y):
		x(x),
		y(y)
	{
	}
};
struct Color4 {
	float r;
	float g;
	float b;
	float a;
	Color4();
	Color4(float r, float g, float b, float a);
	Color4(Vec4f vecA);
};
struct Vec2d
{
	double x;
	double y;
	Vec2d() :
		x(0),
		y(0)
	{}
	Vec2d(double x, double y) :
		x(x),
		y(y)
	{
	}
	operator Vec2f()
	{
		Vec2f Q;
		Q.x = (float)x;
		Q.y = (float)y;
		return (Q);
	}
	Vec2d operator + (Vec2d s)
	{
		double mx = x + s.x;
		double my = y + s.y;
		return { mx,my };
	}
	Vec2d operator - (Vec2d s)
	{
		double mx = x - s.x;
		double my = y - s.y;
		return { mx,my };
	}
};


struct Vec3i
{
	int x;
	int y;
	int z;
	Vec3i(){};
	Vec3i(int x,int y,int z) {
		this->x = x;
		this->y = y;
		this->z = z;
	};
};

