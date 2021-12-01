#pragma once
#include <3dRender/Renderer.h>
#include "MonoResourceManager.h"
#include <UI/InputPoll.h>
#include "uiClusters/RenderFrame.h"
#include <src/MonoScpecific/engine/Scene.h>
namespace monoEngine
{
	class SceneRenderer
	{
		Renderer renderer;
		GLFWwindow* window;
		ResourceManager &resourceManager;
		RenderElement* renderFrame;
		Object CubeObject;
		Object Tree1;
		Object Tree2;
		Object Tree3;
		Object Tree4;
		Object RasterPlane;
		

		Camera cam1;

		std::vector<std::unique_ptr<Object>> objects;

		InputPoll::binAxis<float> CameraMove;

		int materialIndex = 0;
		Scene* activeScene;

		Vec2d mousePos;
		Vec2d mouseMem;
		void moveCamera();
		int getFrameWidth(int screenWidth);
		int getFrameHeight(int screenHeight);
	public:
		SceneRenderer(ResourceManager& resourceManager, GLFWwindow* window, RenderElement* renderFrame);
		void SetAcvtiveScene(Scene* activeScene);
		void draw();
	};
}

