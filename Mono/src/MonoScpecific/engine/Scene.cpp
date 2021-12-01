#include "Scene.h"
#include "monoResourceManagment/SceneLoader.h"
#include <MonoStd/Timer.h>
namespace monoEngine
{
	Scene::Scene(std::string filePath) :
		filePath(filePath),
		Name("@Unknown"),
		versionStr("0.0"),
		author("@Unknown"),
		lastEdit("00:00 : 00.00.0000"), 
		version(0),
		objectCount(0)
	{

	}
}
