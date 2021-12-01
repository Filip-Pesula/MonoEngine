#pragma once
#include <UI/Elements/UiElements.h>
#include <UI/Elements/UiElement.h>
#include "inputElelements/InputElement.h"
#include "MonoScpecific/engine/Efectors/Efector.h"
namespace monoEngine
{
	class EfectorEditor : public UI::UIelement
	{
		UI::Container containter;
		UI::BetterText efectorName;
		std::unique_ptr<Efector>& efector;
		std::vector<std::unique_ptr<InputElement>> itemList;
		
	public:
		EfectorEditor(std::unique_ptr<Efector>& efector, std::vector<std::unique_ptr<InputElement>>& inputList, UI::UIelement* parent);
		void Draw(UI::UIShader shader) override;
		void onResize(Vec2i ScreenSize) override;
		bool onRay(UI::Cursor& cursor) override;
	};
}
