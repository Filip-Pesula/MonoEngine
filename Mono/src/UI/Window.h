#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Custom.h>
#include "UI.h"
namespace UI
{
	class Window
	{
		GLFWwindow* window;
	public:
		uint32_t mWidth;
		uint32_t mHeight;
		const char* mName;
		UI windowUI;
		Window(int width, int height, const char* name);
		Window();
		UI* getUIptr();

		/* Swap front and back buffers */
		void close();
		Vec2i getSize();
		void swapBuffers();
		bool WindowShouldClose();
		GLFWwindow* getWindow();
	};
}

