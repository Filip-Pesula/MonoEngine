#pragma once

struct Vec2f
{
	float x;
	float y;
	Vec2f();
	Vec2f(float x, float y);
	Vec2f operator * (float s);
	Vec2f operator / (float s);
	Vec2f operator + (Vec2f s);
	Vec2f operator - (Vec2f s);
	bool operator == (Vec2f s);
};

struct Vec3f
{
	float x;
	float y;
	float z;
	Vec3f();
	Vec3f(float x, float y, float z);
	Vec3f operator * (float s);
	Vec3f operator / (float s);
	Vec3f operator + (Vec3f s);
	Vec3f operator - (Vec3f s);
	Vec3f operator += (Vec3f s);
	bool operator != (Vec3f s);
};

struct Vec4f
{
	float x;
	float y;
	float z;
	float u;
	Vec4f();
	Vec4f(float x, float y, float z, float u);
	Vec4f(Vec3f vecA, float u);
	Vec4f operator * (float s);
	Vec4f operator / (float s);
	Vec4f operator + (Vec4f s);
	Vec4f operator - (Vec4f s);
	Vec4f operator += (Vec4f s);
	bool operator != (Vec4f s);
};
struct Vec6f
{
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
};