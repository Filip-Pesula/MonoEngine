#pragma once
#include <string>
#include <vector>
class Project
{
	enum buildPipelane {
		MSbuild,
		Cmake
	};
	buildPipelane buildPipelane;


};