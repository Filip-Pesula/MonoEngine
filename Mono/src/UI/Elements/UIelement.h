#pragma once
#include <Custom.h>
#include <UI/Cursor.h>
#include <UI/UIenums.h>
#include <UI/UIshader.h>
#include "BeGL/BeGL.h"
#include <GL/glew.h>
namespace UI
{
	class UIelement
	{
	public:
		UIelement* mParent;
		Unit mWidth;
		Unit mHeight;
		int drawIndex;
		Vec2<Unit> mPosition;
		Vec2f mTop_position;
		Vec2f mBottom_position;
		bool isVisible = true;
	protected:
		GLFWcursor* cursor;
		int mDrawMode;
		bool lastFrameActivation = false;

		float mG_Width;
		float mG_Height;
		/**
		 * @brief position from [-1,1] top-left, to [1,-1] bottom-right
		*/
		Vec2f mG_Position;
		/**
		 * @brief position from [0,0] top-left, to [1,1] bottom-right
		*/
		Vec2f mL_Position;

		std::vector<UIelement*> childList;

	public:
		UIelement(Unit mWidth, Unit mHeight, Vec2<Unit> mPosition, UIelement* mParent);
		UIelement(const UIelement& uiElement, UIelement* mParent);

		UIelement& operator=(const UIelement&) = delete;

		Vec2f getPosition();
		bool getVisible();
		float getG_Width();
		float getG_Height();
		Vec2f getG_Position();
		bool MouseRay(Cursor& cursor);

		//necessary
		virtual void Draw(UIShader shader);
		virtual void Resize(Vec2i screenSize);
		virtual std::unique_ptr<UIelement> clone(UIelement* parent);


	protected:
		void addChild(UIelement* child);
		/**
		 * @brief
		 * function is invoked upon clicking on button
		 * @param mousePos position of mouse relative to element
		 * [0,0]=left-top corner
		 * [1,1]=left-top bottom-right corner
		 *
		*/
		virtual void onClick(Vec2f mousePos, Cursor& cursor);
		/**
		 * @brief
		 * function is invoked upon releasing on button
		 * @param mousePos position of mouse relative to element
		 * [0,0]=left-top corner
		 * [1,1]=left-top bottom-right corner
		 *
		*/
		virtual void onRelease(Vec2f mousePos, Cursor& cursor);
		/**
		 * @brief
		 * function is invoked upon holding on and outside button
		 * @param mousePos position of mouse relative to element
		 * [0,0]=left-top corner
		 * [1,1]=left-top bottom-right corner
		 *
		*/
		virtual void onHold(Vec2f mousePos, Cursor& cursor);
		/**
		 * @brief
		 * function is invoked upon holding on button
		 * @param mousePos position of mouse relative to element
		 * [0,0]=left-top corner
		 * [1,1]=left-top bottom-right corner
		 *
		*/
		virtual void onExit(Vec2f mousePos, Cursor& cursor);
		virtual void onEnter(Vec2f mousePos, Cursor& cursor);
		virtual void onStay(Vec2f mousePos, Cursor& cursor);
		virtual bool onRay(Cursor& cursor);
		virtual void onResize(Vec2i screenSize);

	};
}

