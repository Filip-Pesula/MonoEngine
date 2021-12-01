#pragma once
#include <MonoStd/monoConcepts.h>

template <typename Tname>
struct Vec2
{
	static const size_t SIZE = 2;
	union
	{
		struct
		{
			Tname x;
			Tname y;
		};
		Tname xy[2];

	};

	Vec2() {
	}
	Vec2(Tname x, Tname y) {
		this->x = x;
		this->y = y;
	}
	Tname operator[](std::size_t idx) {
		return xy[idx];
	}
	bool operator==(const Vec2& rhs)
	{
		if (x == rhs.x && y == rhs.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator!=(const Vec2& rhs)
	{
		if (x == rhs.x && y == rhs.y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};

template<mono::Aritmetic_ T>
struct Vec2<T>
{
	static const size_t SIZE = 2;
	union
	{
		struct
		{
			T x;
			T y;
		};
		T xy[2];

	};

	Vec2() {
	}
	Vec2(T x, T y) 
	{
		this->x = x;
		this->y = y;
	}

	T operator[](std::size_t idx) {
		return xy[idx];
	}
	bool operator==(const Vec2& rhs)
	{
		if (x == rhs.x && y == rhs.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator!=(const Vec2& rhs)
	{
		if (x == rhs.x && y == rhs.y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	float magnitude()
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}
	void normalize()
	{
		float mag = magnitude();
		x = x / mag;
		y = y / mag;
	}
	void normalize(float size)
	{
		float mag = magnitude();
		x = (x / mag) * size;
		y = (y / mag) * size;
	}
};




