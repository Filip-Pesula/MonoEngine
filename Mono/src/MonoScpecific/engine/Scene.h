#pragma once
#include <Custom.h>
#include "SceneObject.h"
namespace monoEngine
{
	class Scene
	{
	public:
		std::string filePath;
		std::string Name;
		std::string versionStr;
		std::string author;
		std::string lastEdit;
		int version;
		int objectCount;
		std::vector<std::string> customObjectPath;
		std::vector<std::unique_ptr<SceneObject>> objects;
		Scene(std::string filePath);
	};
}

