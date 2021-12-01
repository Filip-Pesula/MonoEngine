#include "Img.h"
namespace UI
{
	Img::Img(Unit width, Unit height, Color4 color, Vec2<Unit> position, Texture* texture, UIelement* parent):
		UIelement(width,height, position,parent),
		ImgTexture(texture),
		mColor(color)
	{
		mDrawMode = UI::DrawModes::plane_Texture;
	}
	Img::Img(const Img& origin, UIelement* parent):
		UIelement(origin,parent),
		ImgTexture(origin.ImgTexture),
		mColor(origin.mColor)
	{
		mDrawMode = UI::DrawModes::plane_Texture;
	}
	void Img::Draw(UIShader shader)
	{
		if (!getVisible())
		{
			return;
		}
		if (ImgTexture != nullptr)
		{
			ImgTexture->Bind();
		}
		UIShader::RUniforms Uniforms = shader.rUniforms;

		Vec2f lPosition = this->getPosition();
		mG_Position = Vec2f(lPosition.x * 2 - 1 + mG_Width, 1 - lPosition.y * 2 - mG_Height);

		BeGL::setUniform4f(Uniforms.uPosition, mG_Position.x, mG_Position.y, 0, 1);
		BeGL::setUniform4f(Uniforms.uColor, mColor);
		BeGL::setUniform2f(Uniforms.uScale, mG_Width, mG_Height);
		glUniform1i(Uniforms.uTexture, 0);
		glUniform1i(Uniforms.uDrawmode, mDrawMode);
		glUniform1f(Uniforms.uBorder, 0.1f);
		glDrawElements(GL_TRIANGLES, 57, GL_UNSIGNED_INT, nullptr);
	}
	std::unique_ptr<UIelement> Img::clone(UIelement* parent)
	{
		return std::move(std::make_unique<Img>(*this,parent));
	}
}