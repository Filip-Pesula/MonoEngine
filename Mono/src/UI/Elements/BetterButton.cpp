#include "BetterButton.h"
namespace UI
{
	BetterButton::BetterButton(Unit width, Unit height, Color4 stillColor, Color4 focusColor, Vec2<Unit> position, Texture* texture, UIelement* parent):
		UIelement(width,height,position,parent),
		texture(texture),
		onclickListener([]() {}),
		color(stillColor),
		focusColor(focusColor),
		stillColor(stillColor),
		onClickColor(focusColor)
	{
		mDrawMode = UI::DrawModes::plane_Texture;
	}
	BetterButton::BetterButton(Unit width, Unit height, Color4 stillColor, Color4 focusColor, Vec2<Unit> position, UIelement* parent) :
		UIelement(width, height, position, parent),
		texture(nullptr),
		onclickListener([]() {}),
		color(stillColor),
		focusColor(focusColor),
		stillColor(stillColor),
		onClickColor(focusColor)
	{
		mDrawMode = UI::DrawModes::no_Texture;
	}
	BetterButton::BetterButton(const BetterButton& copy,UIelement* parent): 
		UIelement(copy, parent),
		texture(copy.texture),
		onclickListener([](){}),
		color(copy.color),
		focusColor(copy.focusColor),
		stillColor(copy.stillColor),
		onClickColor(copy.onClickColor)
	{
		
	}


	void BetterButton::addOnclickListner(std::function<void()> onclickListener)
	{
		this->onclickListener = onclickListener;
	}

	void BetterButton::onClick(Vec2f mousePos, Cursor& cursor)
	{
		onclickListener();
	}

	void BetterButton::onExit(Vec2f mousePos, Cursor& cursor)
	{
		color = stillColor;
	}

	void BetterButton::onEnter(Vec2f mousePos, Cursor& cursor)
	{
		color = focusColor;
	}

	void BetterButton::Draw(UIShader shader)
	{
		if (!getVisible())
		{
			return;
		}
		if (texture != nullptr)
		{
			texture->Bind();
		}
		UIShader::RUniforms Uniforms = shader.rUniforms;

		Vec2f lPosition = this->getPosition();
		mG_Position = Vec2f(lPosition.x * 2 - 1 + mG_Width, 1 - lPosition.y * 2 - mG_Height);

		BeGL::setUniform4f(Uniforms.uPosition, mG_Position.x, mG_Position.y, 0, 1);
		BeGL::setUniform4f(Uniforms.uColor, color);
		BeGL::setUniform2f(Uniforms.uScale, mG_Width, mG_Height);
		glUniform1i(Uniforms.uTexture, 0);
		glUniform1i(Uniforms.uDrawmode, mDrawMode);
		glUniform1f(Uniforms.uBorder, 0.1f);
		glDrawElements(GL_TRIANGLES, 57, GL_UNSIGNED_INT, nullptr);
	}
	std::unique_ptr<UIelement> BetterButton::clone(UIelement* parent)
	{
		std::unique_ptr<BetterButton> inst = std::make_unique<BetterButton>(*this,parent);
		return std::move(inst);
	}
}