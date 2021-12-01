#include "ScriptEfector.h"
namespace monoEngine
{
    ScriptEfector::ScriptEfector() :
        Efector("ObjectEfector")
    {
    }

    void ScriptEfector::addProperty(std::string name, std::any initVal)
    {
        int newMapIndex = propertyMap.size();
        propertyMap.insert(std::pair(name, std::pair(newMapIndex, initVal)));
    }

    void ScriptEfector::execute()
    {

    }

    std::any ScriptEfector::getProperty(std::string name)
    {
        if (propertyMap.count(name))
        {
            return propertyMap[name].second;
        }
        return std::any();
    }
}
