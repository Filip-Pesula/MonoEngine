#include "Test.h"
#include <resourceManagment/XmlLoader.h>
#include <UI/Elements/UiElements.h>
#include <MonoScpecific/engine/uiClusters/inputElelements/SliderField.h>
#include <resourceManagment/ObjLoader.h>
#include <resourceManagment/XmlDocLoader.h>
int Test::failedTestCount = 0;
int Test::testRan = 0;
std::vector<std::string> Test::failedTests;


void Test::evaluateTests()
{
	std::cout << testRan << " Tests Ran\n";
	std::cout << testRan - failedTestCount << "/" << testRan << " Tests passed\n";
}
void Test::testXmlLoader() {
	XmlLoader xmlLoader{};


	ASSERT_EQUALS(xmlLoader.getXmlContent("res/testXml.xml"), true, "could not load file testXml.xml");

#ifdef TEST
	xmlLoader.test();
#endif // TEST


	

	std::vector<XmlProperty*> sceneObjet = xmlLoader.findObjectsOfName("scene");

	ASSERT_EQUALS(sceneObjet.size(),1, "could not load scene");

	ASSERT_EQUALS(xmlLoader.findAtributeOf("name",sceneObjet[0]),"MainGameScene","could not read name");
	std::vector<XmlProperty*> sceneObjetChildernList = xmlLoader.findAllChildrenOf(sceneObjet[0]);

	ASSERT_GREATHER_THAN(sceneObjetChildernList.size(), 0, "error on");

	std::vector<XmlProperty*> sceneObjectList = xmlLoader.findObjectsInCollection("ObjectList", sceneObjetChildernList);

	ASSERT_EQUALS(sceneObjectList.size(), 1, "error on");

	std::vector<XmlProperty*> sceneObjects = xmlLoader.findChildrenOfObject("Object",sceneObjectList[0]);

	ASSERT_GREATHER_THAN(sceneObjects.size(), 0, "error on");
	
	std::string objectName = xmlLoader.findAtributeOf("name", sceneObjects[0]);
	std::string objectfileRef = xmlLoader.findAtributeOf("fileRef", sceneObjects[0]);


	std::map<std::string, std::string> atributeList = xmlLoader.getAtributesOf(sceneObjects[0]);


	ASSERT_EQUALS(objectName, "Sphere", "object name error");
	ASSERT_EQUALS(objectfileRef, "#1", "object fileRef error");
	ASSERT_THROWS(xmlLoader.findAtributeOf("namename", sceneObjects[0]),std::string("objProperty does not exist"), "object doesn't throw")

	std::string xPosData =  xmlLoader.getObjectContent(xmlLoader.findChildrenOfObject("xPos",sceneObjects[0])[0]);

	ASSERT_EQUALS(xPosData, "0.1" , "could not read xPos Data");
	float xPosf = 0;
	try {
		xPosf = std::stof(xPosData);
	}
	catch (std::invalid_argument e) {

	}
	ASSERT_EQUALS(xPosf, 0.1, "xPos Convertion Error");

	xmlLoader.findAllChildrenOf(sceneObjet[0]);

	XmlDocLoader docLoader;
	docLoader.read("res/testXml.xml");
	ASSERT_NOT_NULLPTR(docLoader.getDoc(),"failed to load file");


}

void TestUI()
{
	monoEngine::SliderField slider(0.f, 1.f, 0.2f, Vec2<Unit> {Unit(), Unit()}, nullptr);
	float val = std::any_cast<float>(slider.getValue());
	UI::BetterText txt(Unit(), Color4(0.1f,1,1,1),"text", nullptr,Vec2<Unit> {Unit(), Unit()}, nullptr);
	UI::BetterText txt2(txt);
	txt2 = UI::BetterText(Unit(), Color4(0.1f, 1, 1, 1), "text", nullptr, Vec2<Unit> {Unit(), Unit()}, nullptr);

}

void TestObjLoader()
{
	
#ifdef TEST
	ObjLoader TreeObj;
	TreeObj.test();
	TreeObj.readObject("3DObjects\\Tree.obj");
#endif // TEST

	
}
