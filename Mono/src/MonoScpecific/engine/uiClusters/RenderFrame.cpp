#include "RenderFrame.h"

Vec2<Unit> monoEngine::RenderElement::getLeftBorderPosition()
{
	return Vec2<Unit>(Unit(),Unit());
}
Vec2<Unit> monoEngine::RenderElement::getTopBorderPosition()
{
	return Vec2<Unit>(Unit(), Unit());
}
Vec2<Unit> monoEngine::RenderElement::getRightBorderPosition(Unit width)
{
	return Vec2<Unit>(width, Unit());
}
Vec2<Unit> monoEngine::RenderElement::getBottomBorderPosition(Unit height)
{
	return Vec2<Unit>( Unit(), height);
}

monoEngine::RenderElement::RenderElement(Unit width, Unit height, Vec2<Unit> position, Color4 borderColor, UI::UIelement* element):
	UIelement(width, height, position, element),
	borderColor(borderColor),
	borderLeft(borderSize, height, borderColor,getLeftBorderPosition(),this),
	borderTop(width, borderSize, borderColor,getLeftBorderPosition(),this),
	borderRight(borderSize, height, borderColor, getRightBorderPosition(width),this),
	borderBottom(width+ borderSize, borderSize, borderColor, getBottomBorderPosition(height),this)
{
}

void monoEngine::RenderElement::Draw(UI::UIShader shader)
{
	borderLeft.Draw(shader);
	borderTop.Draw(shader);
	borderRight.Draw(shader);
	borderBottom.Draw(shader);
}

void monoEngine::RenderElement::onResize(Vec2i screenSize)
{
	borderLeft.Resize(screenSize);
	borderTop.Resize(screenSize);
	borderRight.Resize(screenSize);
	borderBottom.Resize(screenSize);
}

bool monoEngine::RenderElement::onRay(UI::Cursor& cursor)
{
	if (cursor.LMBState == UI::MouseState::PRESS) {
		return true;
	}
	if (cursor.LMBState == UI::MouseState::HOLD) {
		return true;
	}
	return false;
}
