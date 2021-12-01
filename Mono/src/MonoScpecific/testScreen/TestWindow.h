#pragma once
#include <UI/Window.h>
#include <UI/UI.h>
#include <UI/Elements/BetterButton.h>
#include <3dRender/GR_Object.h>
#include <3dRender/Camera.h>
#include <3dRender/Renderer.h>
#include <3dRender/Animator.h>
#include <resourceManagment/ObjLoader.h>
#include "TestResourceManager.h"
#include <UI/InputPoll.h>
#include <MonoStd/monoMath.h>
namespace test
{
	class TestWindow
	{

		UI::Window testWindow = UI::Window(600, 600, "testWindow");
		UI::UI* testUIptr;
		ResourceManager resourceManager;
		Renderer renderer;

		//UI elements
		UI::BetterButton btn;
		UI::BetterButton btn2;
		UI::Slider slider1;
		UI::Slider slider2;
		UI::Slider slider3;
		UI::BetterText text1;


		Object sphereObject;
		Object cottage;
		Object Tree1;
		Object Tree2;
		Object Tree3;
		Object Tree4;
		Object RasterPlane;

		int materialIndex1 = 0;
		int materialIndex = 0;

		Animate animate;

		Camera cam1 = Camera();

		InputPoll::binAxis<float> CameraMove;

		float sppedScale = 1;

		Vec2d mousePos;
		Vec2d mouseMem;

		void moveCamera();
		void moveObject();
	public:
		TestWindow();
		void draw();
		bool WindowShouldClose();
	};
}

