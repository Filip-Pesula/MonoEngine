#pragma once
#include "Custom.h"
#include "iostream"
#include "sstream"
#include <stdlib.h>
#include <type_traits>

#define ASSERT_EQUALS(a, expected , message)  \
	Test::assert_equals(a, expected,message,__FILE__,__LINE__)
#define ASSERT_GREATHER_THAN(a, smaller , message)  \
	Test::assert_greather_than(a, smaller,message,__FILE__,__LINE__)
#define ASSERT_LESS_THAN(a, greather , message)  \
	Test::assert_less_than(a, greather,message,__FILE__,__LINE__)
#define ASSERT_NOT_NULLPTR(a , message)  \
	Test::assert_not_nullptr(a,message,__FILE__,__LINE__)
#define ASSERT_NULLPTR(a , message)  \
	Test::assert_nullptr(a,message,__FILE__,__LINE__)
#define ASSERT_THROWS(a, except , message)  \
try\
{\
	a;\
	std::cout << "\nFunction: -" << #a << "'- does not throw :\n"<< __FILE__ << " " << __LINE__ << "\n";\
}\
catch( decltype(except) e)\
{\
	if(e != except) \
	{\
		std::cout << message << "\nExpected: " << except << " :'" << e << "':\n"<< __FILE__ << " " << __LINE__ << "\n";\
	}\
}

void TestUI();
void TestObjLoader();

template <class T>
concept Printable = requires(std::ostream & os, T a)
{
	os << a;
};
template <class T>
concept equallity_comparable = requires(T a)
{
	a == a;
};


template <class T>
concept equality_assertable = Printable<T> && equallity_comparable<T>;


class Test
{
private:

	static int testRan;
	static int failedTestCount;
	static std::vector<std::string> failedTests;

public:

	static void evaluateTests();

	static void testXmlLoader();
	//template<typename  T, typename U>
	template<typename  T, typename U>
	//requires  equality_assertable<T> && equality_assertable <U>
	requires std::equality_comparable<T> && Printable<T> && std::equality_comparable<U> && Printable <U>
	static constexpr void assert_equals(T a, U expected, std::string message,
		std::string file, size_t line)
	{
		if (a == (T)expected)
		{
			testRan++;
		}
		else
		{
			std::cout << message << "\nExpected: " << expected << " :'" << a << "':\n"<< file << " " << line << "\n";
			failedTests.push_back(message);
			failedTestCount++;
		}
	}

	template<typename  T, typename U>
	static inline void assert_greather_than(T a, U smaller, std::string message,
		std::string file, size_t line)
	{
		if (a > (U)smaller)
		{
			testRan++;
		}
		else
		{
			std::cout << message << ": " << file << " " << line << "\n";
			failedTests.push_back(message);
			failedTestCount++;
		}
	}
	template<typename  T, typename U>
	static inline void assert_less_than(T a, U greather, std::string message,
		std::string file, size_t line)
	{
		if (a < (U)greather)
		{
			testRan++;
		}
		else
		{
			std::cout << message << ": " << file << " " << line << "\n";
			failedTests.push_back(message);
			failedTestCount++;
		}
	}
	template<typename  T>
	static inline void assert_not_nullptr(T a, std::string message,
		std::string file, size_t line)
	{
		if (a != nullptr)
		{
			testRan++;
		}
		else
		{
			std::cout << message << ": " << file << " " << line << "\n";
			failedTests.push_back(message);
			failedTestCount++;
		}
	}
	template<typename  T>
	static inline void assert_nullptr(T a, std::string message,
		std::string file, size_t line)
	{
		if (a == nullptr)
		{
			testRan++;
		}
		else
		{
			std::cout << message << ": " << file << " " << line << "\n";
			failedTests.push_back(message);
			failedTestCount++;
		}
	}
	
};

