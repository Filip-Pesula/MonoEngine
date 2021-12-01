#include "EfectorEditor.h"
#include <MonoScpecific/engine/MonoResourceManager.h>
namespace monoEngine
{

	EfectorEditor::EfectorEditor(std::unique_ptr<Efector>& efector, std::vector<std::unique_ptr<InputElement>>& inputList, UI::UIelement* parent) :
		UIelement(
			Unit(UnitType::pw, 1) - Unit(UnitType::px, 4),
			efector->listContainer->mHeight + Unit(UnitType::px, 4),
			Vec2(
				Unit(UnitType::px, 2),
				Unit(UnitType::px, 2)),
			parent),
		efector(efector),
		itemList(),
		containter(
			Unit(UnitType::pw, 1) - Unit(UnitType::px, 4),
			efector->listContainer->mHeight + Unit(UnitType::px, 4),
			Color4(0.6f, 0.6f, 0.6f, 1.0f),
			Vec2(
				Unit(UnitType::px, 2),
				Unit(UnitType::px, 2)
			),
			parent
		),
		efectorName(
			Unit(UnitType::px, 10),
			Color4(0.0f, 0.0f, 0.0f, 1.0f),
			efector->getName(),
			&ResourceManager::s_inst->textTexture,
			Vec2(
				Unit(UnitType::px, 2),
				Unit(UnitType::px, 2)
			),
			&containter)
	{
		Unit h;
		for (size_t i = 0; i < efector->getPropertyCount(); i++)
		{
			efector->getProperty(i);
		}
		if (inputList.size() > 0) {
			//TODO continue here
			std::unique_ptr<InputElement> inst = std::unique_ptr<InputElement>(inputList[0]->clone_imp(&containter));
			itemList.push_back(std::move(inst));
			int i = 0;
			std::for_each(inputList.begin()+1, inputList.end(), [&](std::unique_ptr<InputElement>& elm) {
				std::unique_ptr<InputElement> inst = std::unique_ptr<InputElement>(elm->clone_imp(itemList[i].get()));
				itemList.push_back(std::move(inst));
				i++;
			});

		}
	}
	void EfectorEditor::Draw(UI::UIShader shader)
	{
		containter.Draw(shader);
		efectorName.Draw(shader);
		for (std::unique_ptr<InputElement>& element: itemList)
		{
			element->Draw(shader);
		}
	}
	void EfectorEditor::onResize(Vec2i ScreenSize)
	{
		containter.Resize(ScreenSize);
		efectorName.Resize(ScreenSize);
		for (std::unique_ptr<InputElement>& element : itemList)
		{
			element->Resize(ScreenSize);
		}
	}
	bool EfectorEditor::onRay(UI::Cursor& cursor)
	{
		int i = 0;
		for (std::unique_ptr<InputElement>& element : itemList)
		{
			element->MouseRay(cursor);
			efector->itemList[i]->setValue(element->getValue());
			i++;
		}
		return false;
	}
}