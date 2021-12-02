#include <rapidxml/rapidxml.hpp>
#include <memory>
#include <string>
class XmlDocLoader {
	std::unique_ptr<rapidxml::xml_document<char>> doc;
public:
	XmlDocLoader();
	void read(std::string name);
	rapidxml::xml_document<char>* getDoc();
};