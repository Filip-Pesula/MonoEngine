#pragma once
#include <Custom.h>
#include <resourceManagment/XmlLoader.h>
#include "../Scene.h"
#include <MonoScpecific/engine/Efectors/MoveEfector.h>
namespace monoEngine
{
	class SceneLoader
	{

		XmlLoader xmlLoader;

		std::string filePath;
		Scene& scene;

		enum SceneLoadingError {
			noSceneInXml = 1,
			noObjectListInXml
		}sceneLoadingError;
		std::string errorMessage;
	public:
		SceneLoader(std::string filePath, Scene& scene);
		int loadScene();
	private:

		XmlProperty* getScene();
		XmlProperty* getObjectList(XmlProperty* sceneObj);
		void getEfectors(XmlProperty* xmlSceneObject, std::unique_ptr<SceneObject>& object);

	};
}
