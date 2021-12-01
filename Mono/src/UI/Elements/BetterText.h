#pragma once
#include "UIelement.h"
#include <Texture.h>
#include <UI/FontRef.h>
namespace UI
{
	class BetterText : public UIelement
	{
	protected:
		Texture* mTexture;
		float* vertexBuffer;
		int vertexBufferSize;
		unsigned int* indexBuffer;
		int indexBufferSize;
		unsigned int vertex;
		unsigned int index;
		Unit mSize;
		std::string mText;
	public:
		Color4 mColor;
	protected:
		inline Unit getTextWidth(const Unit& size, const std::string& text);
		void genText();
	public:
		BetterText(Unit size, Color4 color, std::string text, Texture* texture, Vec2<Unit> position, UIelement* parent);
		BetterText(const BetterText& entity, UIelement* parent) noexcept;
		BetterText(const BetterText& entity) noexcept;
		BetterText(BetterText&& entity) noexcept;
		BetterText& operator = (const BetterText& copy) noexcept;
		BetterText& operator = (BetterText&& move) noexcept;
		void setText(std::string text);
		void Draw(UIShader shader) override;
		~BetterText();
		std::unique_ptr<UIelement> clone(UIelement* parent) override;

	};
}

