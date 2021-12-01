#pragma once
#include <3dRender/Renderer.h>
#include <BeGL/BeGL_FrameBuffer.h>
#include "monoUIshader.h"
#include <UI/UI.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace monoEngine
{
	class MonoRenderrer
	{
		ViewportShader mViewportShader;


		BeGL::GlFrameBuffer mGameBuffer;
		BeGL::GlFrameBuffer mOperatorBuffer;
		Renderer* mSceneRenderrer;
		Renderer* mGameRenderrer;

		UI::UI mainUI;

		GLFWwindow* mRenderWindow;
	public:
		MonoRenderrer(Renderer *gameRenderrer, GLFWwindow* renderWindow)
		{
			mRenderWindow = renderWindow;
			mainUI.InitUI(mRenderWindow);
			mViewportShader = ViewportShader();


			mGameRenderrer = gameRenderrer;
			mGameBuffer = BeGL::GlFrameBuffer(1280,720);
		}
	private:
		void renderScene()
		{
			mGameBuffer.bind();
			mGameRenderrer->Draw();
			mGameBuffer.unbind();
		}
		void renderUI()
		{

		}
		void draw()
		{

		}
	};
}