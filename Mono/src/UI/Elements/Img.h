#pragma once
#include "UIelement.h"
#include <Texture.h>
namespace UI {
	class Img : public UIelement
	{
		Texture* ImgTexture;
	public:
		Color4 mColor;
		Img(Unit width, Unit height, Color4 color, Vec2<Unit> position, Texture* texture, UIelement* parent);
		Img(const Img& origin, UIelement* parent);
		void Draw(UIShader shader)override;
		std::unique_ptr<UIelement> clone(UIelement* parent)override;
	};
}