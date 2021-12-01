#pragma once
#include <Custom.h>
#include <UI/UIenums.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace UI {
	class Cursor
	{
	public:
		Vec2f position;
		Vec2d iPosition;
		MouseState LMBState;
		uint32_t LMBhash;
		MouseState RMBState;
		uint32_t RMBhash;
		GLFWcursor* activeCursor;
	};
}