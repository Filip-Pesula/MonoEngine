#pragma once
#include <Custom.h>
#include <map>
#include <any>
#include "Efector.h"
namespace monoEngine
{
	class ScriptEfector : public Efector
	{
		std::map<std::string, std::pair<int, std::any>> propertyMap;
	public:
		std::string name;

		ScriptEfector();
		void addProperty(std::string name, std::any initVal);
		void execute() override;
		std::any getProperty(std::string name) override;
	};
}
