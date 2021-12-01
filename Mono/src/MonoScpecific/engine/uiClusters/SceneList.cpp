#include "SceneList.h"
namespace monoEngine
{
	SceneList::SceneList(Unit width, Unit height, Vec2<Unit> position, Texture* fontTexture, ObjectEditor& objectEditor, UI::UIelement* parent):
		UIelement(width,height,position,parent),
		listWidth(width),
		listPosition(position),
		objectEditor(objectEditor),
		fontTexture(fontTexture),
		container(
			width,
			height,
			Color4{ 0.3,0.3,0.3,1 },
			position,
			parent
		),
		containerGrabber(
			width,
			Unit(UnitType::px, 10),
			Vec2<Unit>(Unit(), Unit()),
			&container,
			&container
		)
	{

	}
	void SceneList::loadScneList(Scene& scene, float height) {
		Vec2<Unit> position;
		float offset = 7;
		for (size_t i = 0; i < scene.objects.size(); i++)
		{
			position = Vec2<Unit>{
				Unit(UnitType::px,2),
				Unit(UnitType::px,offset)
			};
			std::unique_ptr<UI::BetterButton> btn = std::make_unique<UI::BetterButton>(
				listWidth + Unit(UnitType::px, -4),
				Unit(UnitType::px, height),
				Color4{ 0.32,0.32,0.32,1 },
				Color4{ 0.9,0.9,0.9,1 },
				position,
				&container);
			btn->addOnclickListner([&,i]() {
				objectEditor.setActiveObject(scene.objects[i].get());
				});
			buttonList.push_back(std::move(btn));
			offset += height + 2;

			buttonTextList.push_back(std::make_unique<UI::BetterText>(
				Unit(UnitType::px, height - 4),
				Color4{ 0,0,0,1 },
				scene.objects[i]->Name,
				fontTexture,
				Vec2<Unit>{
				Unit(UnitType::px, 2),
					Unit(UnitType::px, 2)
				},
				buttonList[buttonList.size() - 1].get()
				));


		}
	}

	void SceneList::setInvisible()
	{
		isVisible = false;
		container.isVisible = false;
	}
	void SceneList::Draw(UI::UIShader shader)
	{
		container.Draw(shader);
		for (std::unique_ptr<UI::BetterButton>& btn : buttonList)
		{
			btn->Draw(shader);
		}
		for (std::unique_ptr<UI::BetterText>& txt : buttonTextList)
		{
			txt->Draw(shader);
		}
	}

	void SceneList::onResize(Vec2i screenSize)
	{
		containerGrabber.Resize(screenSize);
		container.Resize(screenSize);
		for (std::unique_ptr<UI::BetterButton>& btn : buttonList)
		{
			btn->Resize(screenSize);
		}
		for (std::unique_ptr<UI::BetterText>& txt : buttonTextList)
		{
			txt->Resize(screenSize);
		}

	}
	bool SceneList::onRay(UI::Cursor& cursor)
	{
		containerGrabber.MouseRay(cursor);
		container.MouseRay(cursor);
		for (std::unique_ptr<UI::BetterButton>& btn : buttonList)
		{
			btn->MouseRay(cursor);
		}
		return false;
	}
	void SceneList::setVisible()
	{
		isVisible = true;
		container.isVisible = true;
	}
}