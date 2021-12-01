#pragma once
#include <Custom.h>
#include <UI/Elements/UiElements.h>
#include <UI/Elements/UiElement.h>
#include <UI/UIenums.h>
#include "../Scene.h"
#include "ObectEfectorEditor.h"
namespace monoEngine
{
	class SceneList : public UI::UIelement
	{
		Unit listWidth;
		Vec2<Unit> listPosition;
		UI::Container container;
		UI::Grabber containerGrabber;
		std::vector<std::unique_ptr<UI::BetterButton>> buttonList;
		std::vector<std::unique_ptr<UI::BetterText>> buttonTextList;
		ObjectEditor& objectEditor;
		Texture* fontTexture;
	public:
		SceneList(Unit width, Unit height, Vec2<Unit> position, Texture* fontTexture, ObjectEditor& objectEditor, UI::UIelement* parent);
		void loadScneList(Scene& scene, float height);
		void setVisible();
		void setInvisible();
		void Draw(UI::UIShader shader) override;
		void onResize(Vec2i screenSize) override;
		bool onRay(UI::Cursor& cursor) override;
	};
}