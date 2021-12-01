#pragma once
#include <UI/Elements/UiElements.h>
#include <3dRender/Renderer.h>
namespace monoEngine
{
	class RenderElement : public UI::UIelement
	{
		const Unit borderSize{ UnitType::px,5 };
		Color4 borderColor;
		UI::Container borderLeft;
		UI::Container borderRight;
		UI::Container borderBottom;
		UI::Container borderTop;
		static Vec2<Unit> getLeftBorderPosition();
		static Vec2<Unit> getRightBorderPosition(Unit width);
		static Vec2<Unit> getTopBorderPosition();
		static Vec2<Unit> getBottomBorderPosition(Unit height);
	public:
		RenderElement(Unit width, Unit height, Vec2<Unit> position, Color4 borderColor, UI::UIelement* element);
		void Draw(UI::UIShader shader) override;
		void onResize(Vec2i screenSize) override;
		bool onRay(UI::Cursor &cursor) override;
	};
}


