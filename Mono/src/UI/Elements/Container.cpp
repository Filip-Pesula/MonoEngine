#include "Container.h"
namespace UI
{
	/*
	* Container
	*/
	Container::Container(Unit width, Unit height, Color4 color, Vec2<Unit> position, UIelement* parent):
		UIelement(width,height,position,parent),
		mColor(color)
	{
	}
	Container::Container(const Container& origin, UIelement* parent):
		UIelement(origin, parent),
		mColor(origin.mColor)
	{
	}
	void Container::Draw(UIShader shader)
	{
		if (!getVisible())
		{
			return;
		}
		UIShader::RUniforms lUniforms = shader.rUniforms;

		Vec2f lPosition = this->getPosition();
		mG_Position = Vec2f(lPosition.x * 2 - 1 + mG_Width, 1 - lPosition.y * 2 - mG_Height);

		BeGL::setUniform4f(lUniforms.uPosition, mG_Position.x, mG_Position.y, 0, 1);
		BeGL::setUniform4f(lUniforms.uColor, mColor);
		BeGL::setUniform2f(lUniforms.uScale, mG_Width, mG_Height);
		glUniform1i(lUniforms.uTexture, 0);
		glUniform1i(lUniforms.uDrawmode, DrawModes::no_Texture);
		glUniform1f(lUniforms.uBorder, 0.02f);
		glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_INT, nullptr);
	}
	std::unique_ptr<UIelement> Container::clone(UIelement* parent)
	{
		return std::move(std::make_unique<Container>(*this,parent));
	}
}