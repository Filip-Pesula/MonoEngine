#pragma once
#include <Custom.h>
#include <map>
class XmlProperty
{
public:
	int propertyStartLine;
	int propertyEndLine;
	int propertyStartChar; //points at first character of property name
	int propertyEndChar;
	int parentPropertyID;
	XmlProperty* parentProperty;
	std::string propertyName;
	XmlProperty(int startLine, int startChar, std::string propertyName, int parent, XmlProperty* parentProperty);
};
class XmlLoader
{

	std::vector<std::unique_ptr<XmlProperty>> xmlPropertyList;
	std::vector<std::string> fileContent;

	void trim(std::string& str);
	void trim(std::string& str, const std::string& trimChar);
	void shrinkToSpace(std::string& str);
	bool isWhitespace(char c);
	std::string elementToLine(XmlProperty* object);
public:
	bool getXmlContent(const std::string& filePath);

	std::vector<XmlProperty*> findObjectsOfName(const std::string& objectName);
	std::vector<XmlProperty*> findObjectsInCollection(const std::string& objectName, std::vector<XmlProperty*> properties);
	std::vector<XmlProperty*> findChildrenOfObject(const std::string& childrenName, XmlProperty* object);
	std::string findAtributeOf(const std::string& propertyName, XmlProperty* object) throw(std::string);
	std::map<std::string, std::string> getAtributesOf(XmlProperty* object);
	std::vector<XmlProperty*> findAllChildrenOf(XmlProperty* xmlProperty);
	std::string getObjectContent(XmlProperty* xmlProperty);

#ifdef TEST
public:
	void test() {
		std::string testStr1 = " TEST_STR  ";
		trim(testStr1);
		ASSERT_EQUALS(testStr1, "TEST_STR", "TrimTestNotWorking"); 
		std::string testStr2 = " TEST STR  ";
		trim(testStr2);
		ASSERT_EQUALS(testStr2, "TEST STR", "TrimTestNotWorking"); 
		std::string testStr3 = "TEST\nSTR ";
		trim(testStr3);
		ASSERT_EQUALS(testStr3, "TEST\nSTR", "TrimTestNotWorking");
	}
#endif
};

