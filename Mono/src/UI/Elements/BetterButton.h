#pragma once
#include "UIelement.h"
#include <functional>
#include <Texture.h>
#include <BeGL/BeGL.h>
#include <UI/UIenums.h>
namespace UI
{
	class BetterButton : public UIelement
	{
		Texture* texture;
		std::function<void()> onclickListener;
	public:
		Color4 color;
		Color4 focusColor;
		Color4 stillColor;
		Color4 onClickColor;
		BetterButton(Unit width, Unit height, Color4 stillColor, Color4 focusColor, Vec2<Unit> position, Texture* texture, UIelement* parent);
		BetterButton(Unit width, Unit height, Color4 stillColor, Color4 focusColor, Vec2<Unit> position, UIelement* parent);
		BetterButton(const BetterButton& copy,UIelement* parent);
		void addOnclickListner(std::function<void()> onclickListener);
		void onClick(Vec2f mousePos, Cursor& cursor) override;
		void onExit(Vec2f mousePos, Cursor& cursor) override;
		void onEnter(Vec2f mousePos, Cursor& cursor) override;
		void Draw(UIShader shader) override;
		std::unique_ptr<UIelement> clone(UIelement* parent) override;
	};
}
