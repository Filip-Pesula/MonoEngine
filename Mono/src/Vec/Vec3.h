#pragma once
#include <MonoStd/monoConcepts.h>
template<typename T>
class Vec3; // forward declare to make function declaration possible

template<typename T> // declaration
std::ostream& operator<<(std::ostream&, const Vec3<T>&);



template <typename Tname>
class Vec3
{
public:
	static const size_t SIZE = 3;
	Tname x;
	Tname y;
	Tname z;
	Vec3() :
		x(),
		y(),
		z()
	{

	}
	Vec3(Tname x, Tname y, Tname z) :
		x(x),
		y(y),
		z(z)
	{
	}
	

	Tname& operator[](std::size_t idx) {
		switch (idx)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return x;
			break;
		}
	}
	const Tname& operator[] (std::size_t idx) const {
		switch (idx)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return x;
			break;
		}
	}

	bool operator==(const Vec3& rhs) const
	{
		if (x == rhs.x && y == rhs.y && z == rhs.z)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator!=(const Vec3& rhs) const
	{
		if (x == rhs.x && y == rhs.y && z == rhs.z)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	friend std::ostream& operator<< <>(std::ostream&, const Vec3&);
};
template<class T>
std::ostream& operator <<(std::ostream& os, const Vec3<T>& L)
{
	os << L.x << " " << L.y << " " << L.z;
	return os;
}


template <typename  Tname> requires mono::Aritmetic_<Tname> && mono::Scalar_f_<Tname,float>
class Vec3<Tname>
{
public:
	static const size_t SIZE = 3;
	Tname x;
	Tname y;
	Tname z;
	Vec3()
	{

	}
	Vec3(Tname x, Tname y, Tname z) :
		x(x),
		y(y),
		z(z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float magnitude()
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

	}
	void normalize()
	{
		float mag = magnitude();
		x = x / mag;
		y = y / mag;
		z = z / mag;
	}
	void normalize(float size)
	{
		float mag = magnitude();
		x = (x / mag) * size;
		y = (y / mag) * size;
		z = (z / mag) * size;
	}

	Tname& operator[](std::size_t idx) {
		switch (idx)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return x;
			break;
		}
	}
	const Tname& operator[] (std::size_t idx) const {
		switch (idx)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return x;
			break;
		}
	}

	bool operator==(const Vec3& rhs) const
	{
		if (x == rhs.x && y == rhs.y && z == rhs.z)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator!=(const Vec3& rhs) const
	{
		if (x == rhs.x && y == rhs.y && z == rhs.z)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	friend std::ostream& operator<< <>(std::ostream& os, const Vec3& node);
};
