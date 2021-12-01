#include "Grabber.h"
namespace UI
{
	Grabber::Grabber(Unit width, Unit height, Vec2<Unit> position, UIelement* itemToGrab, UIelement* parent) :
		UIelement(width, height, position, parent),
		mItemToGrab(itemToGrab)
	{
	}
	Grabber::Grabber(const Grabber& origin, UIelement* parent):
		UIelement(origin, parent),
		mItemToGrab(origin.mItemToGrab)
	{
	}
	void Grabber::Draw(UIShader shader) {}
	std::unique_ptr<UIelement> Grabber::clone(UIelement* parent)
	{
		return std::move(std::make_unique<Grabber>(*this,parent));
	}
	void Grabber::onHold(Vec2f mousePos, Cursor &cursor)
	{
		Vec2f diviation = (Vec2f)cursor.iPosition - lastFrameMousePosition;
		Vec2<Unit> uDiviation;
		uDiviation.x = Unit(  UnitType::px,diviation.x );
		uDiviation.y = Unit(  UnitType::px,diviation.y );
		mItemToGrab->mPosition.x = mItemToGrab->mPosition.x + uDiviation.x;
		mItemToGrab->mPosition.y = mItemToGrab->mPosition.y + uDiviation.y;

		lastFrameMousePosition = cursor.iPosition ;
	}
	void Grabber::onClick(Vec2f mousePos, Cursor &cursor)
	{
		lastFrameMousePosition = cursor.iPosition;
	}
}