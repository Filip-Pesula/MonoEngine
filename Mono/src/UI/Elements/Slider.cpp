#include "Slider.h"
namespace UI
{
	Slider::Slider(Unit width, Unit height, Color4 color, Vec2<Unit> position, UIelement* parent):
		UIelement(width,height,position,parent),
		mColor(color),
		mValue(0)
	{
	}
	Slider::Slider(const Slider& origin, UIelement* parent):
		UIelement(origin, parent),
		mColor(origin.mColor),
		mValue(0)
	{
	}
	void Slider::Draw(UIShader shader)
	{
		if (!getVisible())
		{
			return;
		}
		UIShader::RUniforms Uniforms = shader.rUniforms;

		Vec2f lPosition = this->getPosition();
		mG_Position = Vec2f(lPosition.x * 2 - 1 + mG_Width, 1 - lPosition.y * 2 - mG_Height);

		BeGL::setUniform4f(Uniforms.uPosition, mG_Position.x, mG_Position.y, 0, 1);
		BeGL::setUniform4f(Uniforms.uColor, Vec4f(0.01, 0.01, 0.01, 1));
		BeGL::setUniform2f(Uniforms.uScale, mG_Width, mG_Height);
		glUniform1i(Uniforms.uTexture, 0);
		glUniform1i(Uniforms.uDrawmode, DrawModes::no_Texture);
		glUniform1f(Uniforms.uBorder, 0.02f);
		glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_INT, nullptr);

		float sliderWidth = mG_Width * 0.95;


		BeGL::setUniform4f(Uniforms.uPosition, mG_Position.x, mG_Position.y, 0, 1);
		BeGL::setUniform4f(Uniforms.uColor, Vec4f(0.2, 0.2, 0.2, 1));
		BeGL::setUniform2f(Uniforms.uScale, (sliderWidth), mG_Height * 0.7);
		glUniform1i(Uniforms.uTexture, 0);
		glUniform1i(Uniforms.uDrawmode, DrawModes::no_Texture);
		glUniform1f(Uniforms.uBorder, 0.02f);
		glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_INT, nullptr);

		float sliderPosition = mG_Position.x - sliderWidth * 0.90 + (mG_Width * 0.95 * 0.90 * mValue);
		BeGL::setUniform4f(Uniforms.uPosition, sliderPosition, mG_Position.y, 0, 1);
		BeGL::setUniform4f(Uniforms.uColor, mColor);
		BeGL::setUniform2f(Uniforms.uScale, sliderWidth * (mValue * 0.9 + 0.1), mG_Height * 0.7);
		glUniform1i(Uniforms.uTexture, 0);
		glUniform1i(Uniforms.uDrawmode, DrawModes::no_Texture);
		glUniform1f(Uniforms.uBorder, 0.02f);

		glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_INT, nullptr);
	}
	std::unique_ptr<UIelement> Slider::clone(UIelement* parent)
	{
		std::unique_ptr<Slider> inst = std::make_unique<Slider>(*this,parent);
		return std::move(inst);
	}
	void Slider::onHold(Vec2f mousePos, Cursor &cursor)
	{
		mValue = mousePos.x*1.2 - 0.1;
		if (mValue < 0)
		{
			mValue = 0;
		}
		if (mValue > 1)
		{
			mValue = 1;
		}
	}
}