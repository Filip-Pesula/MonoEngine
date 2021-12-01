#include "SceneObject.h"
namespace monoEngine
{
	SceneObject::SceneObject(std::string objectName, std::string objectPath)
	{
		switch (objectPath[0])
		{
		case '#':
			objectType = ObjectType::engineType;
			objectPath.erase(0);
			break;
		case '~':
			objectType = ObjectType::fileType;
			objectPath.erase(0);
			break;
		default:
			objectType = ObjectType::otherType;
			break;
		}
		this->Path = objectPath;
		Name = objectName;
	}
	SceneObject::SceneObject()
	{
		this->Path = "@unknown";
		this->Name = "@unknown";
		objectType = ObjectType::engineType;
	}
	void SceneObject::setObject()
	{
	}

	void SceneObject::addEfector(std::unique_ptr <Efector> efector)
	{
		efectorList.push_back(move(efector));
	}
}

