#pragma once
#include <src/UI/Elements/UIelement.h>
#include <any>
namespace monoEngine
{
	class InputElement : public UI::UIelement
	{
	public:
		InputElement(Unit width, Unit height, Vec2<Unit> position, UI::UIelement* parent);
		virtual std::any getValue() = 0;
		virtual void setValue(std::any val) = 0;
		virtual std::unique_ptr<UI::UIelement> clone(UI::UIelement* parent) = 0;
		[[nodiscard("POINTER TO CLONE: DISCARD MEANS MEMORRY LEAK")]] virtual InputElement* clone_imp(UI::UIelement* parent) = 0;
	};
}
