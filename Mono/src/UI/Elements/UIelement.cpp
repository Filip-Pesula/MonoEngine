#include "UIelement.h"
namespace UI
{
	/*
	* UIelement
	*/

	/**
	 * @brief
	 * @return
	*/
	Vec2f UIelement::getPosition()
	{
		Vec2f realPosition;
		realPosition = this->mL_Position;
		if (mParent != nullptr)
		{
			realPosition = realPosition + mParent->getPosition();
		}
		return realPosition;
	}
	bool UIelement::getVisible()
	{
		if (isVisible == false)
		{
			return false;
		}
		bool visible;
		if (mParent == nullptr)
		{
			visible = isVisible;
		}
		else if (mParent != nullptr)
		{
			visible = isVisible && mParent->getVisible();
		}
		return visible;
	}

	float UIelement::getG_Width()
	{
		return mG_Width;
	}

	float UIelement::getG_Height()
	{
		return mG_Height;
	}

	Vec2f UIelement::getG_Position()
	{
		return mG_Position;
	}

	bool UIelement::MouseRay(Cursor& cursor)
	{

		if (!getVisible())
		{
			return false;
		}
		Vec2f lPosition = getPosition();

		mG_Position = Vec2f(lPosition.x * 2 - 1 + mG_Width, 1 - lPosition.y * 2 - mG_Height);

		mTop_position.x = lPosition.x;
		mTop_position.y = lPosition.y;
		mBottom_position.x = lPosition.x + mG_Width;
		mBottom_position.y = lPosition.y + mG_Height;
		Vec2f mouseElPos;
		Vec2f mousePos = cursor.position;
		mouseElPos.x = (mousePos.x - lPosition.x) / mG_Width;
		mouseElPos.y = (mousePos.y - lPosition.y) / mG_Height;

		onRay(cursor);
		if (mousePos.x > mTop_position.x && mousePos.x < mBottom_position.x &&
			mousePos.y < mBottom_position.y && mousePos.y > mTop_position.y)
		{
			if (lastFrameActivation)
			{
				onStay(mouseElPos, cursor);
			}
			else
			{
				onEnter(mouseElPos, cursor);
			}
			lastFrameActivation = true;
			switch (cursor.LMBState)
			{
			case MouseState::FREE:
				break;
			case MouseState::PRESS:
				if (cursor.LMBhash == (uint32_t)nullptr) {
					cursor.LMBhash = (uint32_t)this;
				}
				onClick(mouseElPos, cursor);
				break;
			case MouseState::HOLD:
				if (cursor.LMBhash == (uint32_t)this) {
					onHold(mouseElPos, cursor);
				}
				break;
			case MouseState::RELEAS:
				onRelease(mouseElPos, cursor);
				break;
			default:
				Log("mouseState not implimented yet");
			}
			return true;
		}
		else
		{
			if (lastFrameActivation)
			{
				onExit(mouseElPos, cursor);
			}
			lastFrameActivation = false;
			if (cursor.LMBState == MouseState::RELEAS)
			{
				cursor.LMBhash = (uint32_t)nullptr;
			}
			if (cursor.LMBState == MouseState::HOLD && cursor.LMBhash == (uint32_t)this)
			{
				onHold(mouseElPos, cursor);
			}
			return false;
		}
	}
	void UIelement::Draw(UIShader shader)
	{
		static_assert(true, "No Draw function was yet implemented for this element");
		Log("No Draw function was yet implemented for this element");
	}
	void UIelement::Resize(Vec2i screenSize)
	{
		mG_Width = 0;
		mG_Width += mWidth.px / (float)screenSize.x;
		mG_Width += mWidth.sw;
		mG_Width += mWidth.sh;
		if (mParent != nullptr)
		{
			mG_Width += mWidth.pw * mParent->mG_Width;
			mG_Width += mWidth.ph * mParent->mG_Height;
		}

		mG_Height = 0;
		mG_Height += mHeight.px / (float)screenSize.y;
		mG_Height += mHeight.sw;
		mG_Height += mHeight.sh;
		if (mParent != nullptr)
		{
			mG_Height += mHeight.pw * mParent->mG_Width;
			mG_Height += mHeight.ph * mParent->mG_Height;
		}

		mL_Position.x = 0;
		mL_Position.x += mPosition.x.px / (float)screenSize.x;
		mL_Position.x += mPosition.x.sw;
		mL_Position.x += mPosition.x.sh;
		if (mParent != nullptr)
		{
			mL_Position.x += mPosition.x.pw * mParent->mG_Width;
			mL_Position.x += mPosition.x.ph * mParent->mG_Height;
		}

		mL_Position.y = 0;
		mL_Position.y += mPosition.y.px / (float)screenSize.y;
		mL_Position.y += mPosition.y.sw;
		mL_Position.y += mPosition.y.sh;
		if (mParent != nullptr)
		{
			mL_Position.y += mPosition.y.pw * mParent->mG_Width;
			mL_Position.y += mPosition.y.ph * mParent->mG_Height;
		}
		Vec2f lPosition = this->getPosition();
		mG_Position = Vec2f(lPosition.x * 2 - 1 + mG_Width, 1 - lPosition.y * 2 - mG_Height);
		onResize(screenSize);
	}
	std::unique_ptr<UIelement> UIelement::clone(UIelement* parent)
	{
		LogWarn("object is not clonable by type");
		return std::move(std::make_unique<UIelement>(*this));
	}
	void UIelement::addChild(UIelement* child)
	{
		if (child == this) {
			LogError("child cannot be it's own parent");
		}
		else
		{
			childList.push_back(child);
		}
	}
	void UIelement::onClick(Vec2f mousePos, Cursor& cursor)
	{
		//Log("No onClick function was yet implemented for this element");
	}
	void UIelement::onHold(Vec2f mousePos, Cursor& cursor)
	{
		//Log("No onHold function was yet implemented for this element");
	}
	void UIelement::onRelease(Vec2f mousePos, Cursor& cursor)
	{
		//Log("No onRelease function was yet implemented for this element");
	}
	void UIelement::onExit(Vec2f mousePos, Cursor& cursor)
	{
		//Log("No onExit function was yet implemented for this element");
	}
	void UIelement::onEnter(Vec2f mousePos, Cursor& cursor)
	{
		//Log("No onEnter function was yet implemented for this element");
	}
	void UIelement::onStay(Vec2f mousePos, Cursor& cursor)
	{
		//Log("No onStay function was yet implemented for this element" << __FILE__ << __LINE__);
	}
	bool UIelement::onRay(Cursor& cursor)
	{
		//Log("No onEnter function was yet implemented for this element");
		return 0;
	}
	void UIelement::onResize(Vec2i screenSize)
	{
		//Log("No onStay function was yet implemented for this element" << __FILE__ << __LINE__);
	}
	UIelement::UIelement(Unit mWidth,Unit mHeight,Vec2<Unit> mPosition,UIelement* mParent) :
		mWidth(mWidth),
		mHeight(mHeight),
		mPosition(mPosition),
		mParent(mParent),
		mDrawMode(0)
	{
		if (mParent != nullptr) {
			mParent->addChild(this);
		}
	}
	UIelement::UIelement(const UIelement& uiElement, UIelement* mParent):
		mWidth(uiElement.mWidth),
		mHeight(uiElement.mHeight),
		mPosition(uiElement.mPosition),
		mParent(mParent),
		mDrawMode(uiElement.mDrawMode)
	{
		if (mParent != nullptr) {
			mParent->addChild(this);
		}
	}
}