#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <type_traits>
#include <concepts>
namespace mono
{
	template<typename T>
	concept Aritmetic = std::integral<T> || std::floating_point<T>;

	template<Aritmetic T>
	T radToDeg(T rad)
	{
		return (rad * (180.0/M_PI));
	}
	template<Aritmetic T>
	T degToRad(T degree)
	{
		return (degree * (M_PI/180.0));
	}
}
