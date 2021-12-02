#include "XmlDocLoader.h"
#include <iostream>
#include <fstream>
XmlDocLoader::XmlDocLoader():doc(nullptr)
{
}
void XmlDocLoader::read(std::string name)
{

	std::ifstream fileRead;
	fileRead.open(name, std::ios::binary | std::ios::ate);
	if (fileRead.is_open()){
		fileRead.seekg(0, std::ios::end);
		size_t size = fileRead.tellg();
		fileRead.seekg(0);
		char* data = new char[size+1];
		fileRead.read(data, size);
		int red = fileRead.tellg();
		data[size] = 0;
		doc = std::make_unique<rapidxml::xml_document<char>>();
		doc->parse<0>(data);
		delete[] data;
	}
	fileRead.close();
}

rapidxml::xml_document<char>* XmlDocLoader::getDoc()
{
	return doc.get();
}
