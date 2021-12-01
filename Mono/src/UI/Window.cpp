#include "Window.h"
namespace UI
{
	Window::Window(int width, int height, const char* name)
	{
		mWidth = width;
		mHeight = height;
		mName = name;
		window = glfwCreateWindow(mWidth, mHeight, mName, NULL, NULL);
		glfwMakeContextCurrent(window);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		//glDepthRange(0.0f, 10.0f);
		glEnable(GL_LESS);
		glEnable(GL_BLEND);
		windowUI.InitUI(window);
	}
	Window::Window() {}
	UI* Window::getUIptr()
	{
		return &windowUI;
	}
	Vec2i Window::getSize()
	{
		int x = 0; int y = 0;
		glfwGetWindowSize(window,&x,&y);
		return Vec2i{ x , y };
	}
	void Window::swapBuffers()
	{
		glfwSwapBuffers(window);
	}
	bool Window::WindowShouldClose()
	{
		return glfwWindowShouldClose(window);
	}
	GLFWwindow* Window::getWindow()
	{
		return window;
	}
}
