#pragma once
#include <Custom.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace InputPoll
{
	template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	class binAxis
	{
		int mKeyXn;
		int mKeyXp;
		int mKeyYn;
		int mKeyYp;
		GLFWwindow* mWinodw;
	public:
		Vec2<T> Axes;
		binAxis() {}
		binAxis(int keyXn, int keyXp, int keyYp, int keyYn, GLFWwindow* window)
		{
			mKeyXn = keyXn;
			mKeyXp = keyXp;
			mKeyYn = keyYp;
			mKeyYp = keyYn;
			mWinodw = window;
		}
		void get()
		{
			Axes = Vec2<T>(0, 0);
			if (glfwGetKey(mWinodw, mKeyXn))
			{
				Axes.x -= 1;
			}
			if (glfwGetKey(mWinodw, mKeyXp))
			{
				Axes.x += 1;
			}
			if (glfwGetKey(mWinodw, mKeyYn))
			{
				Axes.y -= 1;
			}
			if (glfwGetKey(mWinodw, mKeyYp))
			{
				Axes.y += 1;
			}
		}
	};
}