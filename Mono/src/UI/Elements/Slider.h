#pragma once
#include "UIelement.h"
#include <functional>
#include <Texture.h>
#include <BeGL/BeGL.h>
#include <UI/UIenums.h>
namespace UI 
{
	class Slider : public UIelement
	{
	protected:
		std::function<void()> OnValueChangeListener;
	public:
		Color4 mColor;
		float mValue;
		void onHold(Vec2f mousePos, Cursor& cursor) override;
		Slider(Unit width, Unit height, Color4 color, Vec2<Unit> position, UIelement* parent);
		Slider(const Slider& origin, UIelement* parent);
		void Draw(UIShader shader) override;
		std::unique_ptr<UIelement> clone(UIelement* parent) override;
	};
}