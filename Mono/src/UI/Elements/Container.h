#pragma once
#include "UIelement.h"
namespace UI 
{
	class Container : public UIelement {
	public:
		Color4 mColor;
		Container(Unit width, Unit height, Color4 color, Vec2<Unit> position, UIelement* parent);
		Container(const Container& origin, UIelement* parent);
		void Draw(UIShader shader) override;
		std::unique_ptr<UIelement> clone(UIelement* parent) override;
	};
}