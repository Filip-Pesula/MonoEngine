#pragma once
#include <string>
std::string getMonoScript(std::string fileName)
{
	std::string monoScript =
	"<ProjectName=\""+ fileName +"\">"
	;
	return monoScript;
}