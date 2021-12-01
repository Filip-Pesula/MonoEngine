#include <Mono/Engine.h>
#include <Mono/Custom.h>
#include <iostream>
int Run(const Engine* engine)
{
	Engine engin = *engine;
	Log("Hello World");
	std::cout << "Hello World";
	std::cin.get();
	return 0;
}