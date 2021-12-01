#pragma once
#include "UIelement.h"
namespace UI
{
	class Grabber : public UIelement {
		Vec2f lastFrameMousePosition;
		UIelement* mItemToGrab;
	public:
		Grabber(Unit width, Unit height, Vec2<Unit> position, UIelement* itemToGrab, UIelement* parent);
		Grabber(const Grabber& origin, UIelement* parent);
		void onHold(Vec2f mousePos, Cursor& cursor) override;
		void onClick(Vec2f mousePos, Cursor& cursor) override;
		void Draw(UIShader shader) override;
		std::unique_ptr<UIelement> clone(UIelement* parent) override;
	};
}