#include "SceneLoader.h"
namespace monoEngine
{
	SceneLoader::SceneLoader(std::string filePath, Scene& scene) :
		filePath(filePath),
		scene(scene)
	{

	}
	int SceneLoader::loadScene() {


		xmlLoader.getXmlContent(filePath);

		XmlProperty* sceneObj = getScene();
		if (sceneObj == nullptr)
		{
			errorMessage = "file does not contain Scene";
			return SceneLoadingError::noSceneInXml;
		}

		scene.Name = xmlLoader.findAtributeOf("name", sceneObj);

		//find all scene objects

		XmlProperty* xmlObjList = getObjectList(sceneObj);
		if (xmlObjList == nullptr)
		{
			errorMessage = "file does not contain ObjectList";
			return SceneLoadingError::noObjectListInXml;
		}

		std::vector<XmlProperty*> objectRefList = xmlLoader.findChildrenOfObject("Object", xmlObjList);

		for (XmlProperty* objecRef : objectRefList)
		{
			std::string objectName;
			std::string objectPath;
			try
			{
				objectName = xmlLoader.findAtributeOf("name", objecRef);

			}
			catch (const std::string& e)
			{
				LogError(e << " on object");
				objectName = "@Unknown";
			}
			try
			{
				objectPath = xmlLoader.findAtributeOf("fileRef", objecRef);

			}
			catch (const std::string& e)
			{
				LogWarn(e << " on object");
				objectPath = "@Unknown";
			}


			std::unique_ptr<SceneObject> sceneObject = std::make_unique<SceneObject>(objectName, objectPath);
			getEfectors(objecRef, sceneObject);
			scene.objects.push_back(move(sceneObject));
		}
	}


	XmlProperty* SceneLoader::getScene()
	{
		std::vector<XmlProperty*> sceneObjList = xmlLoader.findObjectsOfName("scene");
		if (sceneObjList.size() == 1)
		{
			return sceneObjList[0];
		}
		return nullptr;
	}

	XmlProperty* SceneLoader::getObjectList(XmlProperty* sceneObj)
	{
		std::vector<XmlProperty*> objList = xmlLoader.findChildrenOfObject("ObjectList", sceneObj);
		if (objList.size() == 1)
		{
			return objList[0];
		}
		return nullptr;
	}

	void SceneLoader::getEfectors(XmlProperty* xmlSceneObject, std::unique_ptr<SceneObject>& object)
	{
		std::vector<XmlProperty*> efectorList = xmlLoader.findChildrenOfObject("Efector", xmlSceneObject);
		if (efectorList.size() == 0)
		{
			LogWarn("MoveEfector is missing");
			std::unique_ptr<MoveEfector> moveEfector = std::make_unique<MoveEfector>();
			moveEfector->setPosition({ 0,0,0 });
			object->addEfector(move(moveEfector));
		}
	}
}



