#include "MenuList.h"
namespace monoEngine
{
	MenuList::MenuList(Unit width, Vec2<Unit> position, UI::UIelement* parent, Texture* fontTexture):
		UIelement(width,Unit(UnitType::px, 2), position, parent),
		listWidth(width),
		listPosition(position),
		container(width,
			Unit(UnitType::px, 2),
			Color4{ 0.3,0.3,0.3,1 },
			Vec2<Unit>(Unit(),Unit()),
			this),
		fontRef(fontTexture)
	{
		mParent=parent;
		isVisible = false;
		container.isVisible = false;
	}
	void MenuList::addElement(std::string text, Unit height) {
		UI::UIelement* refElement;
		Vec2<Unit> position;
		if (buttonList.size() == 0)
		{
			refElement = &container;
			position = Vec2<Unit>{
				Unit{UnitType::px,2},
				Unit{UnitType::px,2}
			};
		}
		else
		{
			refElement = buttonList[buttonList.size()-1];
			position = Vec2<Unit>{
				Unit{UnitType::px, 0},
				refElement->mHeight + Unit(UnitType::px,  2)
			};
		}
		buttonList.push_back(new UI::BetterButton(
			listWidth + Unit(UnitType::px,-4),
			height,
			Color4{ 0.32,0.32,0.32,1 },
			Color4{ 0.9,0.9,0.9,1 },
			position,
			refElement));
		buttonTextList.push_back(new UI::BetterText(
			height + Unit(UnitType::px, -4),
			Color4{ 0,0,0,1 },
			text,
			fontRef,
			Vec2<Unit>{
				Unit{ UnitType::px, 2 },
				Unit{ UnitType::px, 2 }
			},
			buttonList[buttonList.size()-1]
		));
		container.mHeight = container.mHeight + Unit(UnitType::px, 2) + height;
	}
	void MenuList::setElementOnClic(int elemntId, std::function<void(void)> f)
	{
		if (elemntId<0 && elemntId>buttonList.size() - 1) {
			LogError(__FILE__ << " : " << __LINE__ << ": Assigning to incorrect button");
			return;
		}
		buttonList[elemntId]->addOnclickListner(f);
	}
	void MenuList::setInvisible()
	{
		isVisible = false;
		container.isVisible = false;
	}
	bool MenuList::onRay(UI::Cursor& cursor)
	{
		container.MouseRay(cursor);
		for (UI::BetterButton* btn : buttonList)
		{
			btn->MouseRay(cursor);
		}
		return false;
	}
	void MenuList::onResize(Vec2i screenSize)
	{
		container.Resize(screenSize);
		for (UI::BetterButton* btn : buttonList)
		{
			btn->Resize(screenSize);
		}
		for (UI::BetterText* txt : buttonTextList)
		{
			txt->Resize(screenSize);
		}
	}
	void MenuList::Draw(UI::UIShader shader)
	{
		container.Draw(shader);
		for (UI::BetterButton* btn : buttonList)
		{
			btn->Draw(shader);
		}
		for (UI::BetterText* txt : buttonTextList)
		{
			txt->Draw(shader);
		}
	}
	void MenuList::setVisible()
	{
		isVisible = true;
		container.isVisible = true;
	}
}