#include "ObectEfectorEditor.h"

namespace monoEngine
{
	ObjectEditor::ObjectEditor(Unit width, Unit height) :
		UIelement(
			width, 
			height, 
			Vec2<Unit>(
			Unit(UnitType::sw, 1) - Unit(UnitType::px, 200),
			Unit(UnitType::px, 25)
			), 
			nullptr),
		container(
			width,
			height,
			Vec4f(0.4, 0.4, 0.4, 1),
			Vec2<Unit>(
				Unit(UnitType::sw, 1) - Unit(UnitType::px, 200),
				Unit(UnitType::px, 25)
				), nullptr),
		activeObject(nullptr)
	{
		mWidth = width;
		mHeight = height;
	}

	void ObjectEditor::setActiveObject(SceneObject* object)
	{
		activeObject = object;
		efectorList.clear();
		UI::UIelement* conPtr = &container;
		if (activeObject->efectorList.size() == 0)
		{
			return;
		}
		efectorList.push_back(
			std::make_unique<EfectorEditor>(
				activeObject->efectorList[0], 
				activeObject->efectorList[0]->itemList, 
				&container));
		for (int i = 1; i < activeObject->efectorList.size(); i++)
		{
			efectorList.push_back(
				std::make_unique<EfectorEditor>(
					activeObject->efectorList[i], 
					activeObject->efectorList[i]->itemList, 
					efectorList[i-1].get()));
		}
	}

	void ObjectEditor::Draw(UI::UIShader shader)
	{
		container.Draw(shader);
		for (std::unique_ptr<EfectorEditor>& efectorEditor : efectorList)
		{
			efectorEditor->Draw(shader);
		}
	}

	void ObjectEditor::onResize(Vec2i screenSize)
	{
		container.Resize(screenSize);
		for (std::unique_ptr<EfectorEditor>& efectorEditor : efectorList)
		{
			efectorEditor->Resize(screenSize);
		}
	}
	bool ObjectEditor::onRay(UI::Cursor& cursor)
	{
		for (std::unique_ptr<EfectorEditor>& efectorEditor : efectorList)
		{
			efectorEditor->MouseRay(cursor);
		}
		return false;
	}
}