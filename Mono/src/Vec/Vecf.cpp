#include "Vec\Vecf.h"

Vec2f::Vec2f() {}
Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vec2f Vec2f::operator * (float s)
{
	float mx = x * s;
	float my = y * s;
	return { mx,my };
}
Vec2f Vec2f::operator / (float s)
{
	float mx = x / s;
	float my = y / s;
	return { mx,my };
}
Vec2f Vec2f::operator + (Vec2f s)
{
	float mx = x + s.x;
	float my = y + s.y;
	return { mx,my };
}
Vec2f Vec2f::operator - (Vec2f s)
{
	float mx = x - s.x;
	float my = y - s.y;
	return { mx,my };
}
bool Vec2f::operator == (Vec2f s)
{
	if (x == s.x)
	{
		if (y == s.y)
		{
			return true;
		}
	}
	return false;
}

Vec3f::Vec3f() {}
Vec3f::Vec3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vec3f Vec3f::operator * (float s)
{
	float mx = x * s;
	float my = y * s;
	float mz = z * s;
	return { mx,my,mz };
}
Vec3f Vec3f::operator / (float s)
{
	float mx = x / s;
	float my = y / s;
	float mz = z / s;
	return { mx,my,mz };
}
Vec3f Vec3f::operator + (Vec3f s)
{
	float mx = x + s.x;
	float my = y + s.y;
	float mz = z + s.z;
	return { mx,my,mz };
}
Vec3f Vec3f::operator - (Vec3f s)
{
	float mx = x - s.x;
	float my = y - s.y;
	float mz = z - s.z;
	return { mx,my,mz };
}
Vec3f Vec3f::operator += (Vec3f s)
{
	x += +s.x;
	y += +s.y;
	z += +s.z;
	return *this;
}
bool Vec3f::operator != (Vec3f s)
{
	if (s.x == x && s.y == y && s.z == z)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Vec4f::Vec4f() {}
Vec4f::Vec4f(float x, float y, float z, float u)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->u = u;
}
Vec4f::Vec4f(Vec3f vecA, float u)
{
	this->x = vecA.x;
	this->y = vecA.y;
	this->z = vecA.z;
	this->u = u;
}
Vec4f Vec4f::operator * (float s)
{
	float mx = x * s;
	float my = y * s;
	float mz = z * s;
	float mu = u * u;
	return { mx,my,mz,mu };
}
Vec4f Vec4f::operator / (float s)
{
	float mx = x / s;
	float my = y / s;
	float mz = z / s;
	float mu = u / s;
	return { mx,my,mz,mu };
}
Vec4f Vec4f::operator + (Vec4f s)
{
	float mx = x + s.x;
	float my = y + s.y;
	float mz = z + s.z;
	float mu = u + s.u;
	return { mx,my,mz,mu };
}
Vec4f Vec4f::operator - (Vec4f s)
{
	float mx = x - s.x;
	float my = y - s.y;
	float mz = z - s.z;
	float mu = u - s.u;
	return { mx,my,mz,mu };
}
Vec4f Vec4f::operator += (Vec4f s)
{
	x += +s.x;
	y += +s.y;
	z += +s.z;
	u += +s.u;
	return *this;
}
bool Vec4f::operator != (Vec4f s)
{
	if (s.x == x && s.y == y && s.z == z && s.u == u)
	{
		return false;
	}
	else
	{
		return true;
	}
}