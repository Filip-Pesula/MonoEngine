#pragma once
#include <string>
std::string appname = PROJNAME;

namespace Message
{

	std::string HelpMessage =
		R"(
		UnitTest <parent File path> <AppName>
		generates file inside parent file, which is called by App Name
	)";
};
namespace ErrorMessage
{
	std::string NoInput = "no input parametrs were selected use: " + appname + " --help to get more info";
}