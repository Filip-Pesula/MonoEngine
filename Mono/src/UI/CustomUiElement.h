#pragma once
#include <Custom.h>
#include <UI/UIenums.h>
namespace UI
{
	class CustomUIelement
	{
	protected:
		float mG_Width;
		float mG_Height;
		Vec2f mG_Position;
		Vec2f mL_Position;
	public:
		Unit mWidth;
		Unit mHeight;
		Vec2<Unit> mPosition;

		Vec2f getPosition();
		virtual void Draw();
		virtual void Resize(Vec2i screenSize);
	};
}