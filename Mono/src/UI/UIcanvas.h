#pragma once
#include "UI.h"
#include "BeGL/BeGL_FrameBuffer.h"
#include <Custom.h>
namespace UI
{
	class UIcanvas : public UI
	{
		int mFrameBufferWidth = 200;
		int mFrameBufferHeight = 200;
		BeGL::GlFrameBuffer frameBuffer;
		Texture* canvasTexture;
		Vec4f mBackgroundColor;
	public:
		void InitUI(GLFWwindow* window, int width, int heihgt, Vec4f backgroundColor);
		void Draw();
	};
}

