#include "MonoMainWindow.h"
#include "monoResourceManagment/SceneLoader.h"
#include <windows.h>

#include <resourceManagment/FilePathManager.h>


namespace monoEngine
{
	MonoMainWindow::~MonoMainWindow()
	{
	}
	MonoMainWindow::MonoMainWindow() : 
		rightPanel(Unit(UnitType::px, 200), Unit(UnitType::sh, 1))
	{
		mainUIptr = mainEngineWindow.getUIptr();

		SceneLoader sceneLoader(currentScene.filePath, currentScene);
		sceneLoader.loadScene();

		

		renderRelement = std::make_unique <RenderElement>(
			Unit( UnitType::px, 600 ),
			Unit( UnitType::px, 337.5 ),
			Vec2<Unit>(
				Unit(UnitType::sw, 1) - Unit(UnitType::px, 650) - rightPanel.mWidth,
				Unit( UnitType::px, 50 )
			),
			Color4( 0,0,0,1 ),
			nullptr
			);
		mainUIptr->addElement(renderRelement.get());

		objectList = std::make_unique<SceneList>(
			Unit(UnitType::px, 150),
			Unit(UnitType::px, 400),
			Vec2<Unit>(
				Unit(UnitType::px, 50),
				Unit(UnitType::px, 50)
				),
			&resourceManager.textTexture,
			rightPanel,
			nullptr);
		objectList->loadScneList(currentScene, 15);
		mainUIptr->addElement(objectList.get());

		mainUIptr->addElement(&rightPanel);
		sceneRenderer = std::make_unique <SceneRenderer>(resourceManager, mainEngineWindow.getWindow(), renderRelement.get());
		sceneRenderer->SetAcvtiveScene(&currentScene);
		topList = std::make_unique <UI::Container>(
			Unit( UnitType::sw,1 ),
			Unit( UnitType::px,25 ),
			Vec4f(0.5, 0.5, 0.5, 1),
			Vec2<Unit>(
				{ UnitType::sw,0.0 },
				{ UnitType::sw,0.0 }),
			nullptr);
		mainUIptr->addElement(topList.get());
		fileBtn = std::make_unique<UI::BetterButton>(
			Unit( UnitType::px, 50.f ),
			Unit( UnitType::px, 25.f ),
			Vec4f(0.4f, 0.4f, 0.4f, 1.f),
			Vec4f(0.8f, 0.8f, 0.8f, 1.f),
			Vec2<Unit>(
				{ UnitType::sw,0.f },
				{ UnitType::sw,0.f }),
			&resourceManager.woodTexture,
			topList.get());

		fileBtn->addOnclickListner([]() {

		});
		mainUIptr->addElement(fileBtn.get());

		fileBtnText = std::make_unique <UI::BetterText> (
			Unit( UnitType::px, 15 ),
			Vec4f(0, 0, 0, 1), "File",
			&resourceManager.textTexture,
			Vec2<Unit>(
				Unit(UnitType::px,5 ),
				Unit(UnitType::px,5 )
				),
			fileBtn.get());
		mainUIptr->addElement(fileBtnText.get());
		projectBtn = std::make_unique < UI::BetterButton>(
			Unit(UnitType::px, 70.f),
				Unit(UnitType::px, 25.f),
			Vec4f(0.4f, 0.4f, 0.4f, 1.f),
			Vec4f(0.8f, 0.8f, 0.8f, 1.f),
			Vec2<Unit>(
				{ UnitType::px,52.f },
				{ UnitType::sw,0.f }),
			&resourceManager.woodTexture,
			topList.get());
		mainUIptr->addElement(projectBtn.get());

		projectList = std::make_unique<MenuList>(
			Unit(UnitType::px, 90),
			Vec2<Unit>(
				Unit(), 
				Unit(UnitType::px,25)
				),
			projectBtn.get(), 
			&resourceManager.textTexture);
		projectList->addElement("LoadFile",Unit(UnitType::px,15));
		projectList->setElementOnClic(0, []() {
			Log(FilePathManager::OpenFileDialog(nullptr,"G:\\","")[0]);
		});
		projectList->addElement("CreateScene",Unit(UnitType::px,15));
		mainUIptr->addElement(projectList.get());
		projectBtn->addOnclickListner([&]() {
			
				if (activeList == 1) {
					projectList->setInvisible();
					activeList = -1;
				}
				else if (activeList == -1)
				{
					projectList->setVisible();
					activeList = 1;
				}
				
			});

		projectBtnText = std::make_unique <UI::BetterText>(
			Unit( UnitType::px, 15 ),
			Vec4f(0, 0, 0, 1), "Project",
			&resourceManager.textTexture,
			Vec2<Unit>(
				{ UnitType::px,5 },
				{ UnitType::px,5 }),
			projectBtn.get());
		mainUIptr->addElement(projectBtnText.get());
	
		sceneName = std::make_unique < UI::BetterText>(
			Unit(UnitType::px, 15.f),
			Vec4f(0.f, 0.f, 0.f, 1.f), currentScene.Name,
			&resourceManager.textTexture,
			Vec2<Unit>(
				Unit( UnitType::sw,0.80f ),
				Unit( UnitType::px,5.f )
				),
			nullptr);
		mainUIptr->addElement(sceneName.get());
		mainUIptr->addGlobaShortCutListener({ GLFW_KEY_LEFT_CONTROL,GLFW_KEY_S,-1,-1,-1 }, []() {
			FilePathManager::SaveFileDialog(nullptr,"D:\\","");
			});
	}
	void MonoMainWindow::draw()
	{
		glfwMakeContextCurrent(mainEngineWindow.getWindow());
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glClearDepth(1.0f);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mainUIptr->getUI();
		mainUIptr->Draw();
		sceneRenderer->draw();
		mainEngineWindow.swapBuffers();
	}
	bool MonoMainWindow::WindowShouldClose()
	{
		return mainEngineWindow.WindowShouldClose();
	}
}