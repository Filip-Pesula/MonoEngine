#pragma once
#include <Custom.h>
#include <UI/UI.h>
#include <UI/Elements/UIelement.h>
#include <UI/UIenums.h>
namespace monoEngine
{
	class MenuList : public UI::UIelement
	{
		Unit listWidth;
		Vec2<Unit> listPosition;
		UI::Container container; 
		Texture* fontRef;
		std::vector<UI::BetterButton*> buttonList;
		std::vector<UI::BetterText*> buttonTextList;
	public:
		MenuList(Unit width, Vec2<Unit> position, UI::UIelement* parent, Texture* fontTexture);
		void addElement(std::string text, Unit height);
		void setVisible();
		void setInvisible();
		bool onRay(UI::Cursor& cursor) override;
		void onResize(Vec2i screenSize) override;
		void Draw(UI::UIShader shader)override;
	};
}