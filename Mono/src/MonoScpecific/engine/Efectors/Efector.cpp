#include "Efector.h"
namespace monoEngine
{
	Unit Efector::calculatHeight(std::vector<std::unique_ptr<InputElement>>& vecRef)
	{
		Unit h{};
		for (size_t i = 0; i < vecRef.size(); i++) {
			h = h + vecRef[i]->mHeight;
		}
		return h;
	}
	Efector::Efector(std::string name) :
		name(name)
	{

	}
	Efector::Efector(std::string name, std::vector<std::unique_ptr<InputElement>> itemList):
		name(name),
		itemList(std::move(itemList)),
		listContainer(
			std::make_unique<UI::Container>(
				Unit(UnitType::pw,1) - Unit(UnitType::px, 2),
				calculatHeight(Efector::itemList),
				Color4(0,0,0,0),
				Vec2<Unit>(Unit(), Unit()),
				nullptr
				))
	{
	}
	std::string Efector::getName()
	{
		return name;
	}
}
