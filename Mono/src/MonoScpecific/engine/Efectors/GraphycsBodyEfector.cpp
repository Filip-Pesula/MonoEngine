#include "GraphycsBodyEfector.h"

namespace monoEngine
{
	std::vector<std::unique_ptr<InputElement>> GraphycsBodyEfector::generateInputField()
	{
		return std::vector<std::unique_ptr<InputElement>>();
	}
	GraphycsBodyEfector::GraphycsBodyEfector(MoveEfector& moveEfector) :
		Efector("GraphycsBodyEfector", std::move(generateInputField())),
		moveEfector(moveEfector)
	{

	}
	void GraphycsBodyEfector::execute()
	{
	}
	std::any GraphycsBodyEfector::getProperty(std::string name)
	{
		return std::any();
	}
	std::any GraphycsBodyEfector::getProperty(int name)
	{
		return std::any();
	}
	int GraphycsBodyEfector::getPropertyCount()
	{
		return 0;
	}
}
