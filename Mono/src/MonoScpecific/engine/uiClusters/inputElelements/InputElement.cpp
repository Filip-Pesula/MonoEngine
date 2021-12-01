#include "InputElement.h"
namespace monoEngine
{
	InputElement::InputElement(Unit width, Unit height, Vec2<Unit> position,UI::UIelement* parent) :
		UIelement(
			width,
			height,
			position,
			parent)
	{

	}
}