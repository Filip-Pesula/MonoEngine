#pragma once
#include <UI/Window.h>
#include <UI/UI.h>
#include "uiClusters/MenuList.h"
#include "uiClusters/SceneList.h"
#include "uiClusters/RenderFrame.h"
#include "Scene.h"
#include "SceneRenderer.h"
#include "MonoResourceManager.h"
#include "uiClusters/ObectEfectorEditor.h"
namespace monoEngine
{
	class MonoMainWindow
	{
		UI::Window mainEngineWindow = UI::Window(800, 600, "monoEngine");
		UI::UI* mainUIptr;

		ResourceManager resourceManager;

		std::unique_ptr <UI::Container> topList;
		std::unique_ptr <UI::BetterButton> fileBtn;
		std::unique_ptr <UI::BetterText> fileBtnText;
		std::unique_ptr <UI::BetterButton> projectBtn;
		std::unique_ptr <UI::BetterText> projectBtnText;
		std::unique_ptr <UI::BetterText> sceneName;
		
		std::unique_ptr <MenuList> fileList;
		std::unique_ptr <MenuList> projectList;
		std::unique_ptr <MenuList> utilitiesList;

		std::unique_ptr <SceneList> objectList;
		std::unique_ptr <RenderElement> renderRelement;
		std::unique_ptr <SceneRenderer> sceneRenderer;

		ObjectEditor rightPanel;
		


		int activeList = -1;
		Scene currentScene{ "G:\\Programming\\c++\\MonoEngine\\Mono\\res/Scene1.mnsc" };

	public:
		~MonoMainWindow();
		MonoMainWindow();
		void draw();
		bool WindowShouldClose();
	};
}

