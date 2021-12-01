#include "XmlLoader.h"
#include <fstream>
#include <MonoStd/Timer.h>
#include <sstream>
#include <stdexcept>

XmlProperty::XmlProperty(int startLine, int startChar, std::string propertyName, int parentID, XmlProperty* parentProperty) :
	propertyStartLine(startLine),
	propertyEndLine(-1),
	propertyStartChar(startChar),
	propertyEndChar(-1),
	parentPropertyID(parentID),
	parentProperty(parentProperty),
	propertyName(propertyName)
{

}

void XmlLoader::trim(std::string& str)
{
	size_t start = str.find_first_not_of(" \n\t");
	size_t end = str.find_last_not_of(" \n\t");
	str = str.substr(start, (end - start) + 1);
}
void XmlLoader::trim(std::string& str,const std::string& trimChar)
{
	size_t start = str.find_first_not_of(trimChar);
	size_t end = str.find_last_not_of(trimChar);
	str = str.substr(start, (end - start) + 1);
}

void XmlLoader::shrinkToSpace(std::string& str)
{
	for (size_t i = 0; i < str.length()-1; i++)
	{
		if (isWhitespace(str[i]) && isWhitespace(str[i+1]))
		{
			str.erase(i,1);
			str[i] = ' ';
			i--;
		}
	}
}

bool XmlLoader::isWhitespace(char c)
{
	if (c == ' ' || c == '\t')
		return true;
	return false;
}

std::string XmlLoader::elementToLine(XmlProperty* object)
{
	int line = object->propertyStartLine;
	size_t lineCursor = object->propertyStartChar;

	std::string singleLineXmlElement = "";
	if (object->propertyStartLine == object->propertyEndLine)
	{
		size_t elementTail = fileContent[line].find(">", object->propertyStartChar);
		singleLineXmlElement =
			fileContent[line].substr(
				object->propertyStartChar,
				elementTail - object->propertyStartChar
			);
		return singleLineXmlElement;
	}
	else
	{
		int scope = 1;
		size_t cursor = object->propertyStartChar;

		while (scope > 0 && cursor < fileContent[line].size())
		{
			cursor = fileContent[line].find_first_of("<>", cursor + 1);
			if (cursor == std::string::npos)
			{
				cursor = fileContent[line].size() - 1;
				break;
			}
			if (fileContent[line][cursor] == '<')
			{
				scope += 2;
			}
			if (fileContent[line][cursor] == '>')
			{
				scope -= 1;
			}
		}
		if (scope == 0)
		{
			singleLineXmlElement = fileContent[line].substr(object->propertyStartChar, cursor - object->propertyStartChar+1);
		}
		else
		{
			singleLineXmlElement += fileContent[line].substr(object->propertyStartChar, cursor - object->propertyStartChar+1);
			line++;
			cursor = 0;
			while (scope > 0 && line <= object->propertyEndLine)
			{
				while (scope > 0 && cursor < fileContent[line].size())
				{
					cursor = fileContent[line].find_first_of("<>", cursor + 1);
					if (cursor == std::string::npos)
					{
						cursor = fileContent[line].size() - 1;
						break;
					}
					if (fileContent[line][cursor] == '<')
					{
						scope += 2;
					}
					if (fileContent[line][cursor] == '>')
					{
						scope -= 1;
					}
				}
				singleLineXmlElement += " "+ fileContent[line].substr(0, cursor+1);
				line++;
			}
		}
		shrinkToSpace(singleLineXmlElement);
		return singleLineXmlElement;
	}
}

bool XmlLoader::getXmlContent(
	const std::string& filePath)
{
#ifdef Debug
	Timer::LifeTimeTimer timer([=](float time) {
		Log("file _" + filePath + "_: " << time << "\n");
		});
#endif
	std::string line;
	std::ifstream file(filePath);
	if (file.is_open())
	{
		while (getline(file, line, '\n'))
		{
			fileContent.push_back(line);
			size_t propertyOffset = 0;
			size_t offset = 0;
			while (true)
			{
				offset = line.find('<', propertyOffset);
				if (offset == std::string::npos) {
					break;
				}
				size_t offsetEnd1 = line.find(' ', offset + 1);
				offsetEnd1 = (offsetEnd1 == std::string::npos) ? SIZE_MAX : offsetEnd1;
				size_t offsetEnd2 = line.find('>', offset + 1);
				size_t offsetEnd = std::min(offsetEnd1, offsetEnd2);
				std::string propertyName = line.substr(offset + 1, offsetEnd - offset - 1);
				if (propertyName[0] == '/')
				{
					propertyName.erase(0, 1);
					for (int i = xmlPropertyList.size() - 1; i >= 0; i--)
					{
						if (xmlPropertyList[i]->propertyName == propertyName
							&& xmlPropertyList[i]->propertyEndLine == -1)
						{
							xmlPropertyList[i]->propertyEndLine = fileContent.size() - 1;
							xmlPropertyList[i]->propertyEndChar = offset;
							break;
						}
					}
				}
				else if (propertyName[0] == '?')
				{

				}
				else
				{
					int parentID = -1;
					for (int i = xmlPropertyList.size() - 1; i >= 0; i--)
					{
						if (xmlPropertyList[i]->propertyEndLine == -1)
						{
							parentID = i;
							break;
						}
					}
					XmlProperty* parentRef = (parentID == -1) ? nullptr : xmlPropertyList[parentID].get();
					xmlPropertyList.push_back( std::make_unique<XmlProperty>(fileContent.size() - 1, offset, propertyName, parentID, parentRef));
				}
				propertyOffset = offset + 1;
			}

		}
		return true;
	}
	else
	{
		Log("Could not open this file");
		return false;
	}

}

std::vector<XmlProperty*> XmlLoader::findObjectsOfName(const std::string& objectName)
{
	std::vector<XmlProperty*> propertyList;
	for (size_t i = 0; i < xmlPropertyList.size(); i++)
	{
		if (xmlPropertyList[i]->propertyName==objectName)
		{
			propertyList.push_back(xmlPropertyList[i].get());
		}
	}
	return propertyList;
}

std::vector<XmlProperty*> XmlLoader::findObjectsInCollection(const std::string& objectName, std::vector<XmlProperty*> properties)
{
	std::vector<XmlProperty*> propertyList;
	for (size_t i = 0; i < properties.size(); i++)
	{
		if (properties[i]->propertyName == objectName)
		{
			propertyList.push_back(properties[i]);
		}
	}
	return propertyList;
}
std::vector<XmlProperty*> XmlLoader::findChildrenOfObject(const std::string& childrenName,XmlProperty* object)
{
	std::vector<XmlProperty*> childrenCollection = findAllChildrenOf(object);
	std::vector<XmlProperty*> childrenList = findObjectsInCollection(childrenName,childrenCollection);
	return childrenList;
}

std::string XmlLoader::findAtributeOf(const std::string& objAtribute, XmlProperty* object) throw(std::string)
{
	std::map<std::string, std::string> atributeMap = getAtributesOf(object);
	if (atributeMap.count(objAtribute) == 1)
	{
		return atributeMap[objAtribute];
	}
	else
	{
		throw std::string(objAtribute + " does not exist");
		return "";
	}
}

std::map<std::string, std::string> XmlLoader::getAtributesOf(XmlProperty* object)
{
	std::map<std::string, std::string> atributeMap;

	size_t lineCursor = object->propertyStartChar;

	std::string elementHeader = elementToLine(object);
	while (lineCursor < elementHeader.size())
	{
		lineCursor = elementHeader.find_first_of(" \n\t", lineCursor);
		if (lineCursor == elementHeader.size() - 1 || lineCursor == std::string::npos)
		{
			break;
		}
		size_t atributeNameStart = elementHeader.find_first_not_of(" \n\t", lineCursor);
		size_t atributeNameEnd = elementHeader.find("=", lineCursor);
		std::string atributeName = elementHeader.substr(atributeNameStart, atributeNameEnd - atributeNameStart);
		trim(atributeName);
		size_t atributeStart = elementHeader.find("\"", atributeNameEnd);
		size_t atributeEnd = elementHeader.find("\"", atributeStart + 1);
		std::string atribute = elementHeader.substr(atributeStart + 1, atributeEnd - atributeStart - 1);
		atributeMap.insert(std::pair<std::string, std::string>(atributeName, atribute));
		lineCursor = atributeEnd;
	}



	return atributeMap;
}


std::vector<XmlProperty*> XmlLoader::findAllChildrenOf(XmlProperty* xmlProperty)
{
	std::vector<XmlProperty*> childrenList;
	for (size_t i = 0; i < xmlPropertyList.size(); i++)
	{
		if (xmlPropertyList[i]->parentProperty == xmlProperty)
		{
			childrenList.push_back(xmlPropertyList[i].get());
		}
	}
	return childrenList;
}

std::string XmlLoader::getObjectContent(XmlProperty* xmlProperty)
{
	int lineCoursor = xmlProperty->propertyStartLine;
	int charCoursor = xmlProperty->propertyStartChar;
	int contentStartChar = fileContent[xmlProperty->propertyStartLine].find('>', xmlProperty->propertyStartChar);
	charCoursor = contentStartChar+1;
	int bindingCount = 0;
	
	std::stringstream unboundContent;
	while (lineCoursor <= xmlProperty->propertyEndLine)
	{

		std::string line = fileContent[lineCoursor];
		while (charCoursor < (int)line.length())
		{
			if (line[charCoursor] == '<')
			{
				bindingCount += 2;
			}
			if (line[charCoursor] == '>')
			{
				bindingCount--;
			}
			if (bindingCount == 0)
			{
				unboundContent << line[charCoursor];
			}
			charCoursor = 0;
			charCoursor++;
		}
		lineCoursor++;
	}
	return unboundContent.str();
}
