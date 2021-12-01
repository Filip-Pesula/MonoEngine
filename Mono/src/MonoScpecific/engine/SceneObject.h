#pragma once
#include <Custom.h>
#include <map>
#include <any>
#include "Efectors/Efector.h"
namespace monoEngine
{
	class SceneObject
	{
	public:
		enum class ObjectType
		{
			engineType,
			fileType,
			otherType
		} objectType;
		int parent;
		std::string Name;
		std::string Path;
		SceneObject(std::string objectName, std::string objectPath);
		SceneObject();
		void setObject();
		
		//TODO fix this!!!!
		std::vector<std::unique_ptr<Efector>> efectorList;
		void addEfector(std::unique_ptr<Efector> efector);
	};
}

