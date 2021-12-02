#pragma once
#include <Vec\Vec.h>
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
#define LogWarn(x)
#define LogError(x)

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
