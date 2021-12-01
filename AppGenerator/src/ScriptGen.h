#pragma once
#include <string>
std::string RunScript =
"#include <Mono/Engine.h>\n"
"#include <Mono/Custom.h>\n"
"#include <iostream>\n"
"int Run(const Engine *engine)\n"
"{"
"	std::cout << \"Hello World\";\n"
"	std::cin.get();\n"
"	return 0;\n"
"}"
;